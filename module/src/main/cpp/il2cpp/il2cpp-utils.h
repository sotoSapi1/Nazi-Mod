#include "il2cpp-tabledefs.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <unordered_map>

#define DO_API(r, n, p) r (*n) p

#include "il2cpp-api-functions.h"

#undef DO_API

#define DEFAULTS_INIT(field, ns, n) CSharpTypeClass.field = il2cpp_class_from_name(LibImages.Corlib, ns, n);

typedef std::vector<const char*> FieldPattern;
typedef unsigned long long MethodPtr;

bool il2cppApiLoaded = false;
long il2cpp_base = 0;
Il2CppDomain* domain;
size_t libCount;
const Il2CppAssembly** libs;


std::hash<const char*> cacheKeyHasher;
std::unordered_map<uint32_t, Il2CppClass*> classMap;
std::unordered_map<uint32_t, size_t> fieldCache;

#define CONCAT_CHAR(str0, str1) std::string(std::string(str0) + str1).c_str()

#define REG_CLASS(klass, str) RegisterClass(klass, str); return
void RegisterClass(Il2CppClass* klass, const char* name) {
    if(klass == nullptr) {
        LOG_PROPLAM("First Arg (Il2CppClass*) is null");
        return;
    }

    classMap.insert({cacheKeyHasher(name), klass});
}
#define GET_CLASS(str) GetClass(str)
Il2CppClass* GetClass(const char* name) {
    auto it = classMap.find(cacheKeyHasher(name));

    if(it == classMap.end()) {
        LOG_PROPLAM("Can't find %s.", name);
        return nullptr;
    }

    if(it->second == nullptr) {
        LOG_PROPLAM("%s is null", name);
        return nullptr;
    }

    return it->second;
}

struct {
    Il2CppClass* Byte;
    Il2CppClass* Int16;
    Il2CppClass* Int32;
    Il2CppClass* Int64;
    Il2CppClass* Float;
    Il2CppClass* Double;
    Il2CppClass* Char;
    Il2CppClass* String;
    Il2CppClass* Object;
    Il2CppClass* Array;
} CSharpTypeClass;

struct {
    const Il2CppImage* Corlib;
    const Il2CppImage* UnityCoreModule;
    const Il2CppImage* AssemblyCSharp;
} LibImages;


struct SignatureCondition {

    const char* modifier = nullptr;
    const char* typeName = nullptr;
    const char* name = nullptr;
    std::vector<const char*> paramTypeName;
};

void init_il2cpp_api(void *handle) {
#define DO_API(r, n, p) {                      \
    n = (r (*) p) xdl_sym(handle, #n, nullptr);\
}

#include "il2cpp-api-functions.h"

#undef DO_API
}


// TODO: Read List generic thingy then return it as string. Coz il2cpp_type_get_name only returns the type name
std::string ReadList() {

    return "";
}

template<typename T>
T UnboxIl2cppObject(Il2CppObject* obj) {
    return *static_cast<T*>(il2cpp_object_unbox(obj));
}

std::string GetMethodModifier(uint32_t flags) {
    std::stringstream outPut;
    auto access = flags & METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK;

    switch (access) {
        case METHOD_ATTRIBUTE_PRIVATE:
            outPut << "private ";
            break;
        case METHOD_ATTRIBUTE_PUBLIC:
            outPut << "public ";
            break;
        case METHOD_ATTRIBUTE_FAMILY:
            outPut << "protected ";
            break;
        case METHOD_ATTRIBUTE_ASSEM:
        case METHOD_ATTRIBUTE_FAM_AND_ASSEM:
            outPut << "internal ";
            break;
        case METHOD_ATTRIBUTE_FAM_OR_ASSEM:
            outPut << "protected internal ";
            break;
    }
    if (flags & METHOD_ATTRIBUTE_STATIC) {
        outPut << "static ";
    }
    if (flags & METHOD_ATTRIBUTE_ABSTRACT) {
        outPut << "abstract ";
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            outPut << "override ";
        }
    } else if (flags & METHOD_ATTRIBUTE_FINAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_REUSE_SLOT) {
            outPut << "sealed override ";
        }
    } else if (flags & METHOD_ATTRIBUTE_VIRTUAL) {
        if ((flags & METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK) == METHOD_ATTRIBUTE_NEW_SLOT) {
            outPut << "virtual ";
        } else {
            outPut << "override ";
        }
    }
    if (flags & METHOD_ATTRIBUTE_PINVOKE_IMPL) {
        outPut << "extern ";
    }

    return outPut.str();
}

MethodPtr GetMethodPointerFromIndex(Il2CppClass* klass, int index) {

    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass) is null");
        return 0;
    }

    if(klass->method_count <= 0) {
        LOG_PROPLAM("No method founded in %s", il2cpp_class_get_name(klass));
        return 0;
    }

    while(klass->methods == nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    const MethodInfo* method = klass->methods[index];

    if(method == nullptr) {
        LOG_PROPLAM("method at %i is null", index);
    }

    return (MethodPtr) method->methodPointer;
}

MethodPtr GetMethodPointerFromName(Il2CppClass* klass, const char* name, int sameMethodNameSkip = 0) {

    //LOGI("[Info] GetMethodPointerFromName");

    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass) is null. %s", name);
        return 0;
    }

    //const MethodInfo* method = il2cpp_class_get_method_from_name(klass, name, argsCount); // this thing is broken.

    if(klass->method_count <= 0) {
        LOG_PROPLAM("No method founded in %s", il2cpp_class_get_name(klass));
        return 0;
    }

    while (klass->methods == nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    int nig = 0;
    for(int i = 0; i < klass->method_count; i++) {

        const MethodInfo *method = klass->methods[i];

        if(strcmp(il2cpp_method_get_name(method), name) == 0) {

            if(nig < sameMethodNameSkip) {
                nig++;
                continue;
            }

            return (MethodPtr) method->methodPointer;
        }
    }

    //LOGI("[PROPLAM | GetMethodPointerFromName] Can't find %s", name);
    return 0;
}

#define HANDLE_NULL_STR(str) std::string(str == nullptr ? "NULL" : str)
std::string TraceMethod(const SignatureCondition &pattern) {

    std::string out = HANDLE_NULL_STR(pattern.modifier) + HANDLE_NULL_STR(pattern.typeName) + HANDLE_NULL_STR(pattern.name) + " ";

    if(!pattern.paramTypeName.empty()) {

        bool first = true;

        std::string str;

        for(int i = 0; i < std::size(pattern.paramTypeName); i++) {
            str += first ? HANDLE_NULL_STR(pattern.paramTypeName[i]) : ", " + HANDLE_NULL_STR(pattern.paramTypeName[i]);
            first = false;
        }

        out = + "{" + str + "}";
    }

    return out;
}

MethodPtr GetMethodPointer(Il2CppClass* klass, const SignatureCondition &pattern, int indexOffset = 0) {

    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass*) is null. Target: %s", TraceMethod(pattern).c_str());
        return 0;
    }

    //LOGI("Finding %s", TraceMethod(pattern).c_str());

    if(klass->method_count <= 0) {
        LOG_PROPLAM("No method founded in %s", il2cpp_class_get_name(klass));
        return 0;
    }

    while (klass->methods == nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    for(int i = 0; i < klass->method_count; i++) {

        const MethodInfo* method = klass->methods[i];

        int checkScore = 0;

        // 0 = fail, 1 = skipped, 2 = success.
        int test1 = 0, test2 = 0, test3 = 0, test4 = 0;

        uint32_t iflags = 0;
        uint32_t flags = il2cpp_method_get_flags(method, &iflags);

        std::string methodName = il2cpp_method_get_name(method);
        std::string methodModif = GetMethodModifier(flags);
        std::string methodTypeName = il2cpp_class_from_type(il2cpp_method_get_return_type(method))->name;
        int methodParamCount = il2cpp_method_get_param_count(method);

        methodModif.pop_back();

        //LOGI("Name Check %s", BOOL_TO_STRING(pattern.name == methodName));
        if (pattern.name == nullptr) {
            test1 = 1;
            checkScore++;
        }
        else if(methodName == pattern.name) {

            test1 = 2;
            checkScore++;
        }

        //LOGI("modifier Check %s", BOOL_TO_STRING(methodModif == pattern.modifier));
        if (pattern.modifier == nullptr) {
            test2 = 1;
            checkScore++;
        }
        else if(methodModif == pattern.modifier) {
            test2 = 2;
            checkScore++;
        }

        //LOGI("modifier Check %s", BOOL_TO_STRING(pattern.typeName == methodTypeName));
        if (pattern.typeName == nullptr) {
            test3 = 2;
            checkScore++;
        }
        else if(methodTypeName == pattern.typeName) {
            test3 = 2;
            checkScore++;
        }

        //LOGI("paramCount Check %s", BOOL_TO_STRING(pattern.paramCount == methodParamCount));
        if(pattern.paramTypeName.size() > 0 && pattern.paramTypeName.size() == methodParamCount) {

            int successParamScore = 0;

            //LOGI("param Check");
            for (int i2 = 0; i2 < pattern.paramTypeName.size(); ++i2) {

                if (pattern.paramTypeName[i2] != nullptr) {

                    std::string typeName = pattern.paramTypeName[i2];
                    auto paramClass = il2cpp_class_from_type(il2cpp_method_get_param(method, i2));
                    bool is_enum = il2cpp_class_is_enum(paramClass);
                    bool is_value = il2cpp_class_is_valuetype(paramClass);

                    if(typeName == "ENUM" && is_enum) {

                        successParamScore++;
                    }
                    else if(typeName == "VALUE" && is_value && !is_enum) {

                        if(il2cpp_class_is_valuetype(il2cpp_class_from_type(il2cpp_method_get_param(method, i2)))) {

                            successParamScore++;
                        }
                    }
                    else if (typeName == il2cpp_class_from_type(il2cpp_method_get_param(method, i2))->name) {

                        successParamScore++;
                    }

                } else {
                    successParamScore++;
                }
            }

            if (successParamScore == pattern.paramTypeName.size()) {
                test4 = 2;
                checkScore++;
            }
            else
            {
                test4 = 0;
            }

        }
        else if(pattern.paramTypeName.size() == 0) {
            test4 = 1;
            checkScore++;
        }
        else {
            test4 = 0;
        }

        //LOGI("checking score %i", checkScore);
        /*LOGI("[Info] %s: Name Check: %i, Modifier Check: %i, TypeName Check: %i, ParamCount check: %i, ParamTypes check: %i, Check Score: %i",
             methodName.c_str(), test1, test2, test3, test4, test5, checkScore);*/

        if(checkScore >= 4) {

            //LOGI("[Success] Got: %s %s %s | Target: %s %s %s", methodModif.c_str(), methodTypeName.c_str(), methodName.c_str()
            //, pattern.modifier.c_str(), pattern.typeName.c_str(), pattern.name.c_str());
            //LOGI("[Success]  Name Check: %i, Modifier Check: %i, TypeName Check: %i, ParamCount check: %i, ParamTypes check: %i, Check Score: %i",
            //test1, test2, test3, test4, test5, checkScore);

            return (MethodPtr) klass->methods[i + indexOffset]->methodPointer;
        }
    }

    LOG_PROPLAM("Can't find wanted method in %s. Target: %s", klass->name, TraceMethod(pattern).c_str());
    return 0;
}

#define FIELD(_type, name) *(_type *) GetFieldPtr(thsClass, ths, name)
size_t GetFieldPtr(Il2CppClass* klass, void* instancePtr, const char* name, int indexOffset = 0) {

    if(klass == nullptr) {
        LOG_PROPLAM("[PROPLAM] First arg (Il2CppClass) is null. %s", name);
        return 0;
    }

    if(instancePtr == nullptr) {
        LOG_PROPLAM("[PROPLAM] Second arg (void*) Argument is null. %s", name);
        return 0;
    }

    /*uint32_t key = cacheKeyHasher((std::string(il2cpp_type_get_name(il2cpp_class_get_type(klass))) + name + std::to_string(indexOffset)).c_str());

    auto it = fieldCache.find(key);

    if(it != fieldCache.end()) {
        return it->second;
    }*/

    for(int i = 0; i < klass->field_count; i++) {

        auto field = &klass->fields[i];

        if(strcmp(name, field->name) == 0) {
            size_t offset = il2cpp_field_get_offset(&klass->fields[i + indexOffset]);
            //fieldCache.insert({key, offset});
            return (uint64_t) instancePtr + offset;
        }
    }

    LOG_PROPLAM("Can't find wanted Field. %s", name);
    return 0;
}

template<typename T>
T GetStaticField(Il2CppClass* klass, const char* fieldName) {
    void *iter = nullptr;
    while (auto field = il2cpp_class_get_fields(klass, &iter)) { // unoptimized idfc

        if(strcmp(fieldName, il2cpp_field_get_name(field)) == 0) {
            void* var;
            il2cpp_field_static_get_value(field, &var);
            return (T)var;
        }
    }

    return nullptr;
}

template<typename T>
T GetStaticFieldByIndex(Il2CppClass* klass, int index) {

    if(klass == nullptr) {
        return nullptr;
    }

    if(klass->field_count > 0) {
        void* var;
        il2cpp_field_static_get_value(&klass->fields[index], &var);
        return (T)var;
    }

    return nullptr;
}

#define HOOK_UPDATE(klass, ptr) HookUpdate(klass, (void *)ptr, (void **)&old##ptr)
void HookUpdate(Il2CppClass* klass, void* ptr, void** orig) {

    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass*) is null");
        return;
    }

    if(ptr == nullptr) {
        LOG_PROPLAM("Second arg (void*) is null");
        return;
    }

    if(orig == nullptr) {
        LOG_PROPLAM("Third arg (void**) is null");
        return;
    }


    SignatureCondition CON {
            "private",
            "Void",
            "Update"
    };
    MethodPtr POINTER = GetMethodPointer(klass, CON);
    DobbyHook((void*) POINTER, ptr, orig);
}

bool CheckContentCount(Il2CppClass* klass, std::pair<uint32_t, uint32_t> fieldCountPair, std::pair<uint32_t, uint32_t>  methodCountPair)
{
    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass*) is null.");
        return false;
    }

    return klass->field_count >= fieldCountPair.first && klass->field_count <= fieldCountPair.second &&
           klass->method_count >= methodCountPair.first && klass->method_count <= methodCountPair.second; //klass->field_count == fieldCount && klass->method_count == methodCount;
}

float CheckFieldPattern(Il2CppClass* klass, FieldPattern& pattern) {

    if(klass == nullptr) {
        LOG_PROPLAM("First arg (Il2CppClass*) is null.");
        return false;
    }

    int score = 0;

    void* iter = nullptr;
    while(auto field = il2cpp_class_get_fields(klass, &iter)) {

        auto fieldClass = il2cpp_class_from_type(il2cpp_field_get_type(field));

        if(fieldClass == nullptr) {
            continue;
        }

        if(pattern[score] == nullptr) {

            score++;
        }
        else if(strcmp(il2cpp_class_get_name(fieldClass), pattern[score]) == 0) {

            score++;
        }
    }

    return score/pattern.size();
}

monoString* MonoString_new(const char* str) {

    static SignatureCondition funcC = {
            "private static",
            "String",
            "Ctor",
            {"SByte*", "Int32", "Int32"}
    };

    static monoString *(*func)(const char *str, int startIndex, int length) = (monoString* (*)(const char*, int, int))
             GetMethodPointer(CSharpTypeClass.String, funcC);

    return func(str, 0, strlen(str));
}

bool MonoString_equels(monoString* str0, monoString* str1) {

    static bool *(*func)(monoString* str_1, monoString* str_2) =
    (bool* (*)(monoString*, monoString*)) GetMethodPointerFromIndex(CSharpTypeClass.String, 0x16);

    return func(str0, str1);
}

bool MonoString_concat(monoString* str0, monoString* str1) {

    static bool *(*func)(monoString* str_1, monoString* str_2) =
    (bool* (*)(monoString*, monoString*)) GetMethodPointerFromIndex(CSharpTypeClass.String, 0x22);

    return func(str0, str1);
}

bool MonoString_contains(monoString* str0, monoString* str1) {

    static bool *(*func)(monoString* str_1, monoString* str_2) =
    (bool* (*)(monoString*, monoString*)) GetMethodPointerFromIndex(CSharpTypeClass.String, 0x64);

    return func(str0, str1);
}

void MonoString_toUTF8(monoString* str0, char* buffer) {

    static SignatureCondition funcC {"public virtual", "Byte[]", "GetBytes", {"String"}};

    void* (*utf8)() = (void*(*)())
            GetMethodPointerFromName(il2cpp_class_from_name(LibImages.Corlib, "System.Text", "Encoding"), "get_UTF8");

    monoArray<char*>* (*func)(void* instance, monoString* str) = (monoArray<char*>*(*)(void*, monoString*))
            GetMethodPointer(il2cpp_class_from_name(LibImages.Corlib, "System.Text", "Encoding"), funcC);

    strcpy(buffer, reinterpret_cast<char*>(func(utf8(), str0)->vector));
}
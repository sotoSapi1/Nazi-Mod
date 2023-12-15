#pragma once
#include <functional>
#include <string>
#include "imgui.h"
#include "imgui_internal.h"

using namespace ImGui;


float resolutionMul = 0;
#define resMul (100 * resolutionMul)

// these exist cuz binary operands error. i have massive skill issue
inline ImVec2 ImVec2Add(const ImVec2& v1, const ImVec2& v2) {
    return ImVec2(v1.x + v2.x, v1.y + v2.y);
}

inline ImVec2 ImVec2Sub(const ImVec2& v1, const ImVec2& v2) {
    return ImVec2(v1.x - v2.x, v1.y - v2.y);
}

namespace modCol {
    ImVec4 Category = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3499999940395355f);
    ImVec4 CategoryActive = ImVec4(0.4000000059604645f, 0.47843137383461f, 0.7098039388656616f, 0.3f);
    ImVec4 ChildFrame = ImVec4(0.0f, 0.0f, 0.0f, 0.65f);
};

namespace ImGuiModHelper {

    ImGuiStyle copiedStyle;

    std::function<void()> CurrentSubTabDrawFunc = [] {};
    //std::function<void()> CurrentCategoryDrawFunc = []{};

    void RenderTextDisabled(bool isDisabled, const ImVec2& pos_min, const ImVec2& pos_max, const char* text, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect) {
        const char* text_display_end = FindRenderedTextEnd(text, text_end);
        const int text_len = (int)(text_display_end - text);
        if (text_len == 0)
            return;

        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImDrawList* draw_list = window->DrawList;

        ImVec2 pos = pos_min;
        const ImVec2 text_size = text_size_if_known ? *text_size_if_known : CalcTextSize(text, text_display_end, false, 0.0f);

        const ImVec2* clip_min = clip_rect ? &clip_rect->Min : &pos_min;
        const ImVec2* clip_max = clip_rect ? &clip_rect->Max : &pos_max;
        bool need_clipping = (pos.x + text_size.x >= clip_max->x) || (pos.y + text_size.y >= clip_max->y);
        if (clip_rect) // If we had no explicit clipping rectangle then pos==clip_min
            need_clipping |= (pos.x < clip_min->x) || (pos.y < clip_min->y);

        // Align whole block. We should defer that to the better rendering function when we'll have support for individual line alignment.
        if (align.x > 0.0f) pos.x = ImMax(pos.x, pos.x + (pos_max.x - pos.x - text_size.x) * align.x);
        if (align.y > 0.0f) pos.y = ImMax(pos.y, pos.y + (pos_max.y - pos.y - text_size.y) * align.y);

        // Render
        if (need_clipping)
        {
            ImVec4 fine_clip_rect(clip_min->x, clip_min->y, clip_max->x, clip_max->y);
            draw_list->AddText(NULL, 0.0f, pos, GetColorU32(isDisabled ? ImGuiCol_TextDisabled : ImGuiCol_Text), text, text_display_end, 0.0f, &fine_clip_rect);
        }
        else
        {
            draw_list->AddText(NULL, 0.0f, pos, GetColorU32(isDisabled ? ImGuiCol_TextDisabled : ImGuiCol_Text), text, text_display_end, 0.0f, NULL);
        }

    }
}

namespace ImGuiMod {

    void Group(const char* label, const char* str_id, const ImVec2 size_arg, std::function<void()> func) {

        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = GetCurrentWindow();
        ImGui::PushStyleColor(ImGuiCol_ChildBg, modCol::ChildFrame);
        BeginChildEx(str_id, window->GetID(str_id), {size_arg.x, size_arg.y}, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize); {
            //ImGuiWindow* child_window = g.CurrentWindow;
            ImGui::PopStyleColor();
            ImGui::Spacing();
            ImGui::Indent(ImGui::GetStyle().IndentSpacing / 4);
            ImGui::TextUnformatted(label);
            ImGui::Separator();
            func();
            //float autoY = ImMax(0.0f, child_window->ContentSize.y + child_window->WindowPadding.y * 2.0f - child_window->InnerRect.GetHeight());
            //ImGui::SetWindowSize({size_arg.x, GetItemRectSize().y});
            ImGui::EndChild();
        }
    }


    bool Category(const char *label, int categoryId, int* categorySelector, const ImVec2 &size_arg = ImVec2(0, 0), float selectMarkSize = 6.0f, ImGuiButtonFlags flags = 0) {

        ImGuiWindow *window = GetCurrentWindow();
        if(window->SkipItems)
            return false;

        ImGuiContext &g = *GImGui;
        const ImGuiStyle &style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, nullptr, true);

        ImVec2 pos = window->DC.CursorPos;
        if((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
        ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect rect(pos, ImVec2Add(pos, size));
        ItemSize(size, style.FramePadding.y);
        if(!ItemAdd(rect, id))
            return false;

        if(g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
            flags |= ImGuiButtonFlags_Repeat;

        bool hovered, held;
        bool pressed = ButtonBehavior(rect, id, &hovered, &held, flags);
        bool wantedCategory = *categorySelector == categoryId;

        // Render
        const ImU32 col = GetColorU32( wantedCategory ? modCol::CategoryActive : ImVec4(0,0,0,0));
        RenderNavHighlight(rect, id);

        RenderFrame(ImVec2Sub(rect.Min, ImVec2(size_arg.x * 0.10, 0)), ImVec2Sub(rect.Max, ImVec2(size_arg.x * 0.10, 0)), GetColorU32(col), false, 30);

        if(wantedCategory) {
            RenderFrame(ImVec2Sub(rect.Min, ImVec2(size_arg.x * 0.96, 0)), ImVec2Sub(rect.Max, ImVec2(size_arg.x * 0.96, 0)), GetColorU32(ImGuiCol_ButtonActive), true, style.FrameRounding);
        }

        ImGuiModHelper::RenderTextDisabled(!wantedCategory, ImVec2Add(rect.Min, style.FramePadding), ImVec2Sub(rect.Max, style.FramePadding), label, nullptr, &label_size, style.ButtonTextAlign, &rect);

        // Automatically close popups
        //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
        //    CloseCurrentPopup();

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);

        if(pressed) {
            *categorySelector = categoryId;
        }

        return pressed;

    }

    bool CategorySubTab(const char *label, int subTabId, int* subTabSelector, std::function<void()> drawFunc){


        const ImVec2 size_arg = ImVec2(0,0);

        ImGuiWindow *window = GetCurrentWindow();
        if(window->SkipItems)
            return false;

        ImGuiContext &g = *GImGui;
        const ImGuiStyle &style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, nullptr, true);

        ImVec2 pos = window->DC.CursorPos;
        if(style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
        ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect rect(pos, ImVec2Add(pos, size));
        ItemSize(size, style.FramePadding.y);
        if(!ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(rect, id, &hovered, &held, 0);
        bool wantedSubTab = *subTabSelector == subTabId;

        // Render
        //const ImU32 col = GetColorU32(wantedSubTab ? modCol::CategoryActive : ImVec4(0,0,0,0));
        RenderNavHighlight(rect, id);

        //RenderFrame(rect.Min, ImVec2Sub(rect.Max, ImVec2(20, 0)), GetColorU32(col), false, 30);

        if(wantedSubTab) {
            ImGuiModHelper::CurrentSubTabDrawFunc = drawFunc;
            RenderFrame(ImVec2Sub(rect.Min, ImVec2(0, size.y * 0.92)),ImVec2Sub(rect.Max, ImVec2(0, size.y * 0.92)), GetColorU32(ImGuiCol_ButtonActive), true, 0);
        }

        ImGuiModHelper::RenderTextDisabled(!wantedSubTab, ImVec2Add(rect.Min, style.FramePadding), ImVec2Sub(rect.Max, style.FramePadding), label, nullptr, &label_size, style.ButtonTextAlign, &rect);

        // Automatically close popups
        //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
        //    CloseCurrentPopup();

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);

        if(pressed) {

            *subTabSelector = subTabId;
        }

        ImGui::SameLine();

        return pressed;
    }
}
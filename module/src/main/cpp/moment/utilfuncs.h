#include <random>

#define SafeCall(func, ...) if(func) { func(__VA_ARGS__); } else { LOG_PROPLAM(#func " is null") }

void *get_PlayerTransform(void *player) {

    void* plrTrans = *(void **) GetFieldPtr(GET_CLASS("Player_move_c"), player, "myPlayerTransform");

    if(plrTrans == nullptr) {
        LOG_PROPLAM("Can't find myPlayerTransform field.");
        return nullptr;
    }

    return Component$get_transform(plrTrans);
}

Vector3 get_PlayerVec(void *player) {
    return Transform$get_position(get_PlayerTransform(player));
}

void set_PlayerVec(void *player, Vector3 pos) {
    void* trans = get_PlayerTransform(player);
    Transform$set_position(trans, pos);
}

void *get_PlayerSkinName(void *player) {
    return *(void **) GetFieldPtr(GET_CLASS("Player_move_c"), player, "mySkinName");
}

bool get_PlayerIsMine(void *player) {
    if(player == nullptr) return false;
    return *(bool*) GetFieldPtr(GET_CLASS("SkinName"), get_PlayerSkinName(player), "isMine");
}

void *get_PlayerDamageable(void *player) {
    return *(void **) GetFieldPtr(GET_CLASS("Player_move_c"), player, "mySkinName", -5);
}

bool IsEnemyTo(void *localPlayer, void *player) {
    static bool (*IsEnemy)(void *x, void *y) = (bool (*)(void *, void *)) GetMethodPointerFromName(GET_CLASS("PlayerDamageable"), "IsEnemyTo");
    return IsEnemy(get_PlayerDamageable(localPlayer), player);
}

void *findNearestPlayer(void *localPlayer, monoList<void **> *playerArray) {
    void *nearestPlayer = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    Vector3 localPlayerPos = get_PlayerVec(localPlayer);
    for(int i = 0; i < playerArray->getSize(); ++i) {
        void *player = playerArray->getItems()[i];

        if(get_PlayerIsMine(player) || !IsEnemyTo(localPlayer, player)) continue;

        Vector3 otherPlayerPos = get_PlayerVec(player);
        float distance = Vector3::Distance(localPlayerPos, otherPlayerPos);
        if(distance < minDistance && localPlayer != player) {
            minDistance = distance;
            nearestPlayer = player;
        }
    }
    return nearestPlayer;
}

std::vector<void *> findPlayersInRadius(monoList<void **> *playerArray, void *myPlayer, float radius) {
    std::vector<void *> playersInRadius;
    for (int i = 0; i < playerArray->getSize(); ++i) {
        void *player = playerArray->getItems()[i];

        if (get_PlayerIsMine(player) || IsEnemyTo(myPlayer, player)) continue;

        Vector3 otherPlayerPos = get_PlayerVec(player);
        if (Vector3::Distance(get_PlayerVec(myPlayer), otherPlayerPos) <= radius) {
            playersInRadius.push_back(player);
        }

    }
    return playersInRadius;
}
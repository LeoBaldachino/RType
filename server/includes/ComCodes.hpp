#pragma once

namespace RType {
    /**
     * @brief all the communications codes, see the documentation about thoses codes at 
     * 
     */
    enum ComCodes {
        moveAnEntity = 11,
        valueSet = 12,
        removeEntity = 13,
        keyPressed = 14,
        entityType = 16,
        newPlayerConnected = 21,
        playerDeconnected = 22,
        newRoomIsCreated = 23,
        listOfRooms = 24,
        getListOfRooms = 25,
        destroyedRoom = 26,
        playerPing = 27,
        playerGetId = 28,
        givePlayerId = 29,
        illegalAction = 31,
        serverStop = 32,
        cannotRead = 33,
        resendMessage = 34,
    };
}
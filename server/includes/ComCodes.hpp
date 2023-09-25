#pragma once

namespace RType {
    /**
     * @brief all the communications codes, see the documentation about thoses codes at 
     * 
     */
    enum ComCodes {
        move = 11,
        valueChange = 12,
        touchingObject = 13,
        keyPressed = 14,

        newPlayerConnected = 21,
        playerDeconnected = 22,
        newRoomIsCreated = 23,
        listOfRooms = 24,
        getListOfRooms = 25,
        destroyedRoom = 26,
        illegalAction = 31,
    };
}
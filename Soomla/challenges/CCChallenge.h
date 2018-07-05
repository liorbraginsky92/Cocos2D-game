/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */


#ifndef __CCChallenge_H_
#define __CCChallenge_H_

#include "CCMission.h"

namespace soomla {

    /**
     @class CCChallenge
     @brief A challenge is a specific type of `Mission` which holds a collection
     of `Mission`s. The user is required to complete all these `Mission`s in
     order to earn the `Reward` associated with the `Challenge`.
     */
    class CCChallenge: public CCMission {

        friend class CCChallengeEventHandler;

        CC_SYNTHESIZE_RETAIN(cocos2d::__Array *, mMissions, Missions);
        CC_SYNTHESIZE_RETAIN(cocos2d::EventListener *, mMissionCompletionRevokedListener, MissionCompletionRevokedListener);

    public:

        CCChallenge(): CCMission(), mMissions(NULL), mMissionCompletionRevokedListener(NULL) {
        }

        /**
         Creates an instance of `CCChallenge`.
         @param id `Challenge` ID.
         @param name `Challenge` name.
         @param missions `Mission`s that belong to this `Challenge`.
         @param rewards `Reward`s associated with this `Challenge`.
         */
        static CCChallenge *create(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *missions = NULL, cocos2d::__Array *rewards = NULL);

        SL_CREATE_WITH_DICTIONARY(CCChallenge);

        bool init(cocos2d::__String *id, cocos2d::__String *name,
                cocos2d::__Array *missions = NULL, cocos2d::__Array *rewards = NULL);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCChallenge();

        virtual const char *getType() const;

        /**
         Converts this `CCChallenge` to a Dictionary.
         @return The Dictionary that represents this `CCChallenge`.
         */
        virtual cocos2d::__Dictionary* toDictionary();

        /**
         Checks if this `CCChallenge` is completed.
         @return If this instance is completed returns `true`; otherwise `false`.
         */
        virtual bool isCompleted();

    protected:

        /**
         Registers relevant events: `OnMissionCompleted` and
         `OnMissionCompletionRevoked`.
         */
        void registerEvents();

        /**
         Unregisters relevant events: `OnMissionCompleted` and
         `OnMissionCompletionRevoked`.
         */
        void unregisterEvents();
        
        void onMissionCompleted(cocos2d::EventCustom *event);
        void onMissionCompletionRevoked(cocos2d::EventCustom *event);
    };
}

#endif //__CCChallenge_H_

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


#ifndef __CCSocialActionGate_H_
#define __CCSocialActionGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCUserProfileUtils.h"

namespace soomla {

    /**
     NOTE: Social `Gate`s require the user to perform a specific social
     action in order to open the `Gate`. Currently, the social provider that's
     available is Facebook, so the `Gates`s are FB-oriented. In the future,
     more social providers will be added.

     This is an abstract class that all social `Gate`s must implement.
     */
    class CCSocialActionGate: public CCGate {
        CC_SYNTHESIZE(cocos2d::EventListener *, mEventListener, EventListener);
        CC_SYNTHESIZE(CCProvider, mProvider, Provider);

    public:
        CCSocialActionGate(): CCGate(), mProvider(FACEBOOK), mEventListener(NULL) {
        }

        virtual bool init(cocos2d::__String *id, CCProvider provider);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        /**
         Converts this `SocialActionGate` to a Dictionary.
         @return The Dictionary representation of this `CCSocialActionGate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCSocialActionGate();

    protected:

        /**
         Checks if this `Gate` meets its criteria for opening.
         @return Always `true`.
         */
        virtual bool canOpenInner();

        /**
         Registers relevant events: social-action-finished event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: social-action-finished event.
         */
        virtual void unregisterEvents();
        
        void onSocialActionFinishedEvent(cocos2d::EventCustom *event);

    private:
        void fillProviderFromDict(cocos2d::__Dictionary *dict);
        void putProviderToDict(cocos2d::__Dictionary *dict);
    };
}

#endif //__CCSocialActionGate_H_

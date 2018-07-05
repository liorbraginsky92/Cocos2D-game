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



#ifndef __CCWorldCompletionGate_H_
#define __CCWorldCompletionGate_H_

#include "CCGate.h"
#include "CCLevelUpConsts.h"
#include "CCWorld.h"

namespace soomla {

    /**
     A specific type of `Gate` that has an associated world. The `Gate` opens
     once the `World` has been completed.
     */
    class CCWorldCompletionGate: public CCGate {
        friend class CCWorldCompletionGateEventHanler;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedWorldId, AssociatedWorldId, CCLevelUpConsts::JSON_LU_ASSOCWORLDID)
        CC_SYNTHESIZE_RETAIN(cocos2d::EventListener *, mEventListener, EventListener);

    public:

        CCWorldCompletionGate(): CCGate(), mAssociatedWorldId(NULL), mEventListener(NULL) {
        }

        /**
         Constructor.
         @param id ID.
         @param associatedWorldId Associated world ID.
         */
        static CCWorldCompletionGate *create(cocos2d::__String *id, cocos2d::__String *associatedWorldId);

        SL_CREATE_WITH_DICTIONARY(CCWorldCompletionGate)
        bool init(cocos2d::__String *id, cocos2d::__String *associatedWorldId);

        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual const char *getType() const;

        /**
         Converts this `Gate` to a Dictionary.
         @return The Dictionary representation of this `Gate`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCWorldCompletionGate();

    protected:

        /**
         Registers relevant events: world-completed event.
         */
        virtual void registerEvents();

        /**
         Unregisters relevant events: world-completed event.
         */
        virtual void unregisterEvents();

        /**
         Checks if this `Gate` meets its criteria for opening, by checking that
         the associated world is not null and has been completed.
         @return If this `World` can be opened returns `true`; otherwise `false`.
         */
        virtual bool canOpenInner();

        /**
         Opens this `Gate` if it can be opened (its criteria has been met).
         @return Upon success of opening returns `true`; otherwise `false`.
         */
        virtual bool openInner();
        
        void onWorldCompleted(cocos2d::EventCustom *event);
    };
}

#endif //__CCWorldCompletionGate_H_

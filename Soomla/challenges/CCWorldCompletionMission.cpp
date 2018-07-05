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

#include "CCWorldCompletionMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    USING_NS_CC;

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__String *associatedWorldId) {
        return create(id, name, NULL, associatedWorldId);
    }

    CCWorldCompletionMission *CCWorldCompletionMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, cocos2d::__String *associatedWorldId) {
        CCWorldCompletionMission *ret = new CCWorldCompletionMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_GATE),
                CCCoreConsts::JSON_JSON_TYPE);
        dict->setObject(associatedWorldId, CCLevelUpConsts::JSON_LU_ASSOCWORLDID);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCWorldCompletionMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_WORLD_COMPLETION_MISSION;
    }
}

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

#include "CCSocialStatusMission.h"
#include "CCLevelUpConsts.h"

namespace soomla {

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::__String *id, cocos2d::__String *name, CCProvider provider, cocos2d::__String *status) {
        return CCSocialStatusMission::create(id, name, NULL, provider, status);
    }

    CCSocialStatusMission *CCSocialStatusMission::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Array *rewards, CCProvider provider, cocos2d::__String *status) {
        CCSocialStatusMission *ret = new CCSocialStatusMission();

        __Dictionary *dict = __Dictionary::create();
        dict->setObject(__String::create(CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_GATE),
                CCCoreConsts::JSON_JSON_TYPE);
        dict->setObject(CCUserProfileUtils::providerEnumToString(provider), CCLevelUpConsts::JSON_LU_SOCIAL_PROVIDER);
        dict->setObject(status, CCLevelUpConsts::JSON_LU_STATUS);
        if (ret->init(id, name, rewards, dict)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    const char *CCSocialStatusMission::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_SOCIAL_STATUS_MISSION;
    }

}

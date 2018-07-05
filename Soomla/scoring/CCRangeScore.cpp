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



#include "CCRangeScore.h"

namespace soomla {

    CCRangeScore *CCRangeScore::create(cocos2d::__String *id, CCSRange *range) {
        return CCRangeScore::create(id, NULL, NULL, range);
    }

    CCRangeScore *CCRangeScore::create(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range) {
        CCRangeScore *ret = new CCRangeScore();
        if (ret->init(id, name, higherBetter, range)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCRangeScore::init(cocos2d::__String *id, cocos2d::__String *name, cocos2d::__Bool *higherBetter, CCSRange *range) {
        bool result = CCScore::init(id, name, higherBetter);
        if (result) {
            setRange(range);
            return true;
        }
        return result;
    }

    bool CCRangeScore::initWithDictionary(cocos2d::__Dictionary *dict) {
        bool result = CCScore::initWithDictionary(dict);
        if (result) {
            cocos2d::__Dictionary *rangeDict = dynamic_cast<cocos2d::__Dictionary *>(
                    dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE));
            if (rangeDict) {
                setRange(CCSRange::createWithDictionary(rangeDict));
            }
            return true;
        }
        return result;
    }

    cocos2d::__Dictionary *CCRangeScore::toDictionary() {
        cocos2d::__Dictionary *dict = CCScore::toDictionary();

        if (mRange) {
            dict->setObject(mRange->toDictionary(), CCLevelUpConsts::JSON_LU_SCORE_RANGE);
        }

        return dict;
    }


    void CCRangeScore::inc(double amount) {
        // Don't increment if we've hit the range's highest value
        if (mTempScore >= mRange->mHigh) {
            return;
        }

        if ((mTempScore+amount) > mRange->mHigh) {
            amount = mRange->mHigh - mTempScore;
        }

        CCScore::inc(amount);
    }

    void CCRangeScore::dec(double amount) {
        // Don't decrement if we've hit the range's lowest value
        if (mTempScore <= mRange->mLow) {
            return;
        }

        if ((mTempScore-amount) < mRange->mLow) {
            amount = mTempScore - mRange->mLow;
        }

        CCScore::dec(amount);
    }

    void CCRangeScore::setTempScore(double score, bool onlyIfBetter) {
        if (score > mRange->mHigh) {
            score = mRange->mHigh;
        }
        if (score < mRange->mLow) {
            score = mRange->mLow;
        }

        CCScore::setTempScore(score, onlyIfBetter);
    }

    CCSRange *CCSRange::create(double low, double high) {
        CCSRange *ret = new CCSRange();
        if (ret->init(low, high)) {
            ret->autorelease();
        }
        else {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    bool CCSRange::init(double low, double high) {
        this->mLow = low;
        this->mHigh = high;
        return true;
    }

    bool CCSRange::initWithDictionary(cocos2d::__Dictionary *dict) {
        cocos2d::Ref *ref;
        cocos2d::__Double *aDouble;

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        aDouble = dynamic_cast<cocos2d::__Double *>(ref);
        if (aDouble) {
            this->mLow = aDouble->getValue();
        }
        else {
            this->mLow = 0.0;
        }

        ref = dict->objectForKey(CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);
        aDouble = dynamic_cast<cocos2d::__Double *>(ref);
        if (aDouble) {
            this->mHigh = aDouble->getValue();
        }
        else {
            this->mHigh = 0.0;
        }

        return true;
    }

    cocos2d::__Dictionary *CCSRange::toDictionary() {
        cocos2d::__Dictionary *dict = cocos2d::__Dictionary::create();

        dict->setObject(cocos2d::__Double::create(mLow), CCLevelUpConsts::JSON_LU_SCORE_RANGE_LOW);
        dict->setObject(cocos2d::__Double::create(mHigh), CCLevelUpConsts::JSON_LU_SCORE_RANGE_HIGH);

        return dict;
    }

    char const *CCRangeScore::getType() const {
        return CCLevelUpConsts::JSON_JSON_TYPE_RANGE_SCORE;
    }
}

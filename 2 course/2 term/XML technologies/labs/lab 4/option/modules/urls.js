import {accessToken, version} from "./consts.js";

class Urls {
    constructor() {
        this.url = 'https://api.vk.com/method'
        this.commonInfo = `access_token=${accessToken}&v=${version}`
    }

    getUserInfo(userId) {
        if (!userId) {
            console.error("Не указан userId для getUserInfo");
            return null;
        }
        return `${this.url}/users.get?user_ids=${userId}&fields=photo_400_orig,sex,bdate,country,city,occupation&${this.commonInfo}`
    }

    getGroupMembers(groupId, filter) {
        if (!groupId) {
            console.error("Не указан groupId для getGroupMembers");
            return null;
        }
        const filterString = filter ? `&filter=${filter}` : '';
        return `${this.url}/groups.getMembers?group_id=${groupId}&fields=photo_400_orig&${this.commonInfo}${filterString}`
    }
}

export const urls = new Urls()
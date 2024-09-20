const tabMenuData = require('./tabMenuData')

class TabMenu {
    constructor(data) {
        this.text = data.text ? data.text : "";
        this.isActive = data.isActive != null ? data.isActive : false;
    }
}

class MenuModel {
    constructor(tabsData = tabMenuData) {
        this.tabList = tabsData.map(tabData => new TabMenu(tabData))
        this.activeTab = this.tabList.find(tab => tab.isActive) || this.tabList[0]
    }

    // findActiveTab() {
    //     return this.tabList.find(tab => tab.isActive) || this.tabList[0]
    // }

    setActiveTab(tabItem) {
        this.tabList.forEach(tab => {
            tab.isActive = (tab.text === tabItem.text);
        });
        this.activeTab = tabItem;
    }

    getActiveTab() {
        return this.activeTab;
    }

    getTabList() {
        return this.tabList;
    }
}

module.exports = {
    MenuModel
};
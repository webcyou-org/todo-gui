const { createMenuItem } = require('./component/menuComponent')

class MenuView {
    constructor() {
        this.menu = document.getElementById('menuList');
    }

    renderTabList(tabList) {
        this.menu.innerHTML = '';
        tabList.forEach(tab => {
            const tabItem = createMenuItem(tab);
            tabItem.addEventListener('click', (event) => {
                event.preventDefault();
                this.onTabClick(tab)
            });
            this.menu.appendChild(tabItem);
        });
    }

    bindTabClick(handler) {
        this.onTabClick = handler;
    }
}

module.exports = {
    MenuView
};
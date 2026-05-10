export function renderTabs(tabs, onSelect) {
  const container = document.getElementById('tabs-area');
  container.innerHTML = '';
  tabs.forEach((tab) => {
    const btn = document.createElement('button');
    btn.className = 'tab-btn' + (tab.isActive ? ' active' : '');
    btn.textContent = tab.text;
    btn.addEventListener('click', async () => {
      await goSetActiveTab(tab.text);
      onSelect();
    });
    container.appendChild(btn);
  });
}
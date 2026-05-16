import SwiftUI

struct ContentView: View {
    @StateObject private var appState = AppState()

    var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            Text("ToDo")
                .font(.system(size: 18, weight: .bold))
                .foregroundColor(Theme.white)
                .padding(.bottom, 14)

            TodoInputView { task in appState.addTodo(task) }
                .padding(.bottom, 14)

            TabMenuView(activeFilter: $appState.activeFilter)
                .padding(.bottom, 3)

            TodoListView()
        }
        .padding(.horizontal, 24)
        .padding(.vertical, 10)
        .frame(maxWidth: .infinity, maxHeight: .infinity, alignment: .topLeading)
        .background(Theme.bg)
        .environmentObject(appState)  // inject for all descendants
    }
}
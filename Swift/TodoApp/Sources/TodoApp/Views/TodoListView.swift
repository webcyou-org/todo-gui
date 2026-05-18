import SwiftUI

struct TodoListView: View {
    @EnvironmentObject var appState: AppState

    var body: some View {
        ScrollView {
            VStack(spacing: 5) {
                ForEach(appState.filteredTodos) { todo in
                    TodoItemRow(todo: todo)
                }
            }
        }
    }
}

private struct TodoItemRow: View {
    let todo: Todo
    @EnvironmentObject var appState: AppState

    var body: some View {
        HStack(spacing: 0) {
            ZStack {
                Circle()
                    .fill(Color.clear)
                    .overlay(
                        Circle().stroke(
                            Theme.cbBorder,
                            lineWidth: 2
                        )
                    )
                if todo.isCompleted {
                    Path { p in
                        p.move(to: CGPoint(x: 4, y: 8))
                        p.addLine(to: CGPoint(x: 7, y: 11))
                        p.addLine(to: CGPoint(x: 12, y: 5))
                    }
                    .stroke(Theme.accent, style: StrokeStyle(lineWidth: 1.5, lineCap: .round, lineJoin: .round))
                }
            }
            .frame(width: 16, height: 16)

            Spacer().frame(width: 18)

            Text(todo.task)
                .font(.system(size: 14))
                .foregroundColor(todo.isCompleted ? Theme.muted : Theme.text)
                .strikethrough(todo.isCompleted, color: Theme.muted)
                .frame(maxWidth: .infinity, alignment: .leading)
        }
        .padding(.horizontal, 10)
        .frame(height: 35)
        .background(Theme.surface)
        .cornerRadius(4)
        // contentShape makes the full row hittable, simultaneousGesture
        // fires alongside NSScrollView's pan so it isn't swallowed
        .contentShape(Rectangle())
        .simultaneousGesture(
            TapGesture().onEnded { appState.toggleCompleted(id: todo.id) }
        )
    }
}
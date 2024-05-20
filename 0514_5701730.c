#include <stdio.h>

#define MAX_LIST_SIZE 100
//배열리스트 프로그램
typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size;
} ArrayListType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
}

void init(ArrayListType* L) {
    L->size = 0;
}

int is_full(ArrayListType* L) {
    return (L->size == MAX_LIST_SIZE);
}

int is_empty(ArrayListType* L) {
    return (L->size == 0);
}

int insert_element(ArrayListType* L, int pos, element item) {
    if (is_full(L) || pos < 0 || pos > L->size) {
        return -1;  
    }

    int move_count = 0;
    for (int i = L->size - 1; i >= pos; i--) {
        L->array[i + 1] = L->array[i];
        move_count++;
    }

    L->array[pos] = item;
    L->size++;
    return move_count;
}

int delete_element(ArrayListType* L, int pos) {
    if (is_empty(L) || pos < 0 || pos >= L->size) {
        return -1;  // 실패 시 -1 반환
    }

    int move_count = 0;
    element item = L->array[pos];
    for (int i = pos; i < L->size - 1; i++) {
        L->array[i] = L->array[i + 1];
        move_count++;
    }

    L->size--;
    return move_count;
}

void print_list(ArrayListType* L) {
    printf("[LIST]");
    for (int i = 0; i < L->size; i++)
        printf(" <%d>", L->array[i]);
    printf("\n");
}

int main() {
    ArrayListType list;
    init(&list);
    int choice, num, position, moves;

    while (1) {
        printf("\n메뉴:\n");
        printf("1. 리스트에 추가\n");
        printf("2. 리스트에서 삭제\n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료\n");
        printf("선택 : ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            if (is_full(&list)) {
                printf("리스트가 꽉 찼습니다.\n");
            }
            else {
                printf("추가할 숫자 입력: ");
                scanf_s("%d", &num);
                printf("추가할 위치 입력: ");
                scanf_s("%d", &position);
                moves = insert_element(&list, position, num);
                if (moves == -1)
                    printf("추가 실패: 유효하지 않은 위치 또는 리스트가 가득 찼습니다.\n");
                else
                    printf("%d번 데이터 이동\n", moves);
            }
            break;
        case 2:
            if (is_empty(&list)) {
                printf("리스트가 비어 있습니다.\n");
            }
            else {
                printf("삭제할 위치 입력: ");
                scanf_s("%d", &position);
                moves = delete_element(&list, position);
                if (moves == -1)
                    printf("삭제 실패: 유효하지 않은 위치 또는 리스트가 비어 있습니다.\n");
                else
                    printf("%d번 데이터 이동\n", moves);
            }
            break;
        case 3:
            print_list(&list);
            break;
        case 0:
            printf("프로그램 종료\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }

    return 0;
}

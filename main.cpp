#include <iostream>

using namespace std;

typedef unsigned int UINT;

struct list_t {
    int * list;
    UINT size;
    UINT capability;
};

struct return_v {
    int val;
    int err;
};

void info(list_t * arr) {
    cout << "Data: [";
    for (int i = 0; i < arr->size; i++) {
        cout << " " << arr->list[i];
    }
    cout << " ] Size: <" << arr->size << "> ";
    cout << "Capability: <" << arr->capability << ">";
    cout << endl;
}

list_t * create_list(UINT capability = 1) {
    list_t * arr = new list_t;
    arr->size = 0;
    arr->capability = capability;
    arr->list = new int[capability];
    return arr;
}

list_t * append(list_t * arr, int elem) {
    if (arr->size == arr->capability) {
        list_t * arr_new = new list_t;
        arr_new->size = arr->size;
        arr_new->capability = arr->capability * 2;
        arr_new->list = new int[arr->capability];
        for (int i = 0; i < arr->size; i++) {
            arr_new->list[i] = arr->list[i];
        }
        delete[] arr->list;
        delete arr;
        arr = arr_new;
    }
    arr->list[arr->size] = elem;
    arr->size++;
    return arr;
}

return_v * get(list_t * arr, int index) {
    return_v * result = new return_v;
    if (index < arr->size) {
        result->err = 0;
        result->val = arr->list[index];
    } else {
        result->err = 1;
    }
    return result;
}

int index(list_t * arr, int value) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->list[i] == value) {
            return i;
        }
    }
    return -1;
}

void clear(list_t * arr) {
    delete[] arr->list;
    delete arr;
}

int main() {
    auto arr = create_list(3);
    arr = append(arr, 1);
    arr = append(arr, 2);
    arr = append(arr, 3);
    arr = append(arr, 4);
    info(arr);

    auto val = get(arr, 4);
    if (!val->err) {
        cout << val->val << endl;
    }

    arr = append(arr, 5);
    info(arr);

    val = get(arr, 4);
    if (!val->err) {
        cout << val->val << endl;
    }
    delete val;
    
    int idx = index(arr, 6);
    cout << idx << endl;
    
    idx = index(arr, 5);
    cout << idx << endl;
    
    clear(arr);

    return 0;
}

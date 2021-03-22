#include <iostream>
#include <vector>

using namespace std;

class SparseList {
public:
    SparseList() {
        arr = new int[0];
        _size = 0;
    }

    SparseList(int n) {
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = 0;
        }
        _size = n;
    }

    int size() {
        return _size;
    }

    void remove(int ind) {
        arr[ind] = 0;
        decreaseDistance(ind);
    }

    int get(int index) {
        return arr[index];
    }

    void set(int index, int data) {
        if (index >= _size) {
            this->resize(index + 1);
        }
        if (arr[index] == 0 && data != 0) {
            insertNonZeroDistance(index);
        }
        if (arr[index] != 0 && data == 0) {
            removeNonZeroDistance(index);
        }
        arr[index] = data;
    }

    void sortNonEmpty() {
        if (nonZeroDistances.size() <= 1) {
            return;
        }

        vector<int> indexes;
        int current = _size - nonZeroDistances[nonZeroDistances.size() - 1];
        indexes.push_back(current);
        for (int i = nonZeroDistances.size() - 2; i > 0; ) {
            current = current - nonZeroDistances[i];
            indexes.push_back(current);
        }
        indexes.push_back(nonZeroDistances[0]);

        for (int i = 0; i < indexes.size() - 1; i++) {
            for (int j = 1; j < indexes.size(); j++) {
                if (arr[indexes[j]] < arr[indexes[j - 1]]) {
                    int temp = arr[indexes[j]];
                    arr[indexes[j]] = arr[indexes[j - 1]];
                    arr[indexes[j - 1]] = temp;
                }
            }
        } 
    }

    void displayDistances() {
        cout << "{ ";
        for (int i = 0; i < nonZeroDistances.size(); i++) {
            cout << nonZeroDistances[i] << ' ';
        }
        cout << " }\n";
    }   

    void displayAll() {
        cout << "{ ";
        for (int i = 0; i < _size; i++) {
            cout << arr[i] << " ";
        }
        cout << " }\n";
    }

private:
    void resize(int n) {
        int* newArr = new int[20];
        for (int i = 0; i < _size; i++) {
            newArr[i] = arr[i];
        }

        for (int i = _size; i < n; i++) {
            newArr[i] = 0;
        }

        delete arr;
        arr = newArr;
        _size = n;
    }

    void insertNonZeroDistance(int ind) {
        if (nonZeroDistances.size() == 0) {
            nonZeroDistances.push_back(ind);
            return;
        }
        else if (nonZeroDistances.size() == 1) {
            if (nonZeroDistances[0] > ind) {
                nonZeroDistances.push_back(_size - ind);
            }
            else {
                nonZeroDistances[0] = _size - nonZeroDistances[0];
                nonZeroDistances.insert(nonZeroDistances.begin(), ind);
            }
        }

        vector<int> indexes;
        int current = _size - nonZeroDistances[nonZeroDistances.size() - 1];
        indexes.push_back(current);
        for (int i = nonZeroDistances.size() - 2; i > 0; i--) {
            current = current - nonZeroDistances[i];
            indexes.push_back(current);
        }
        indexes.push_back(nonZeroDistances[0]);

        bool found = false;
        for (int i = 0; i < indexes.size(); i++) {
            if (ind < indexes[i]) {
                indexes.insert(indexes.begin() + i, ind);
                found = true;
                break;
            }
        }
        
        if (!found) {
            indexes.push_back(ind);
        }
        //indexes are in reverse order
        nonZeroDistances.resize(0);
        current = _size - indexes[0];
        nonZeroDistances.push_back(current);
        for (int i = 1; i < indexes.size() - 1; i++) {
            current = indexes[i - 1] - indexes[i];
            nonZeroDistances.insert(nonZeroDistances.begin(), current);
        }
        nonZeroDistances.insert(nonZeroDistances.begin(), indexes[indexes.size() - 1]);
    }

    void removeNonZeroDistance(int ind) { //TODO
        if (nonZeroDistances.size() < 2) {
            nonZeroDistances.resize(0);
            return;
        } else if (nonZeroDistances.size() == 2) {
            if (ind == nonZeroDistances[0]) {
                nonZeroDistances.erase(nonZeroDistances.begin() + 1);
            } else {
                nonZeroDistances[1] = _size - nonZeroDistances[1];
                nonZeroDistances.erase(nonZeroDistances.begin());
            }
            return;
        }

        vector<int> indexes;
        int current = _size - nonZeroDistances[nonZeroDistances.size() - 1];
        indexes.push_back(current);
        for (int i = nonZeroDistances.size() - 2; i > 0; ) {
            current = current - nonZeroDistances[i];
            indexes.push_back(current);
        }
        indexes.push_back(nonZeroDistances[0]);

        for (int i = 0; i < indexes.size(); i++) {
            indexes.erase(indexes.begin() + i);
        }

        nonZeroDistances.resize(0);
        current = _size - indexes[0];
        nonZeroDistances.push_back(current);
        for (int i = 1; i < indexes.size() - 1; i++) {
            current = indexes[i - 1] - indexes[i];
            nonZeroDistances.insert(nonZeroDistances.begin(), current);
        }
        nonZeroDistances.insert(nonZeroDistances.begin(), indexes[indexes.size() - 1]);
    }

    void decreaseDistance(int ind) {   //TODO
        if (ind > _size - nonZeroDistances[nonZeroDistances.size() - 1]) {
            return;
        }

        int prevElem = 0;
        int prev = _size;
        int current;
        for (int i = nonZeroDistances.size() - 1; i > 0; i--) {
            current = prev - nonZeroDistances[i];
            if (current < ind && ind < prev) {
                nonZeroDistances[i + 1] -= 1;
                break;
            }

            if (current == ind) {
                nonZeroDistances.erase(nonZeroDistances.begin() + i);
                if (i != 1) {
                    nonZeroDistances[i - 1] += nonZeroDistances[i];
                }
                return;
            } else {
                int temp = arr[current];
                arr[current] = 0;
                arr[current - 1] = temp;
            }
            prev = current;
        }
    }

    vector<int> nonZeroDistances;
    int* arr;
    int _size;
};

int main()
{
    SparseList* L = new SparseList(10);
    L->set(3, 10);
    L->set(8, 20);
    L->displayAll();
    L->set(20, 111);
    L->displayAll();
    cout << L->size();
}

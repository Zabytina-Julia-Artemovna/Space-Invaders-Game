#include <iostream>
#include <Windows.h>
#include "../Include/tvector.h"
void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}
namespace TestSystem {
    int count_success = 0, count_failed = 0;

    void start_test(bool(*test)(), const char* name_of_test) {
        set_color(2, 0);
        std::cout << "[ RUN      ]";
        set_color(7, 0);
        std::cout << name_of_test << std::endl;
        bool status = test();
        if (status == true) {
            set_color(2, 0);
            std::cout << "[       OK ]" << std::endl;
            count_success++;
        }
        else {
            set_color(4, 0);
            std::cout << "[  FAILED  ]" << std::endl;
            count_failed++;
        }
        set_color(7, 0);
    }

    template <class T>
    bool check(const T& expected, const T& actual) {
        if (expected == actual) {
            return true;
        }
        else {
            std::cerr << "Expected result is " << expected << " but actual is " << actual << std::endl;
            return false;
        }
    }

    void print_final_info() {
        set_color(2, 0);
        std::cout << "[==========] ";
        set_color(7, 0);
        std::cout << count_success + count_failed << " test" << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
        set_color(2, 0);
        std::cout << "[  PASSED  ] ";
        set_color(7, 0);
        std::cout << count_success << " test" << (count_success > 1 ? "s" : "") << std::endl;
        if (count_failed > 0) {
            set_color(4, 0);
            std::cout << "[  FAILED  ] ";
            set_color(7, 0);
            std::cout << count_failed << " test" << (count_failed > 1 ? "s." : ".") << std::endl;
        }
    }
};
bool test_1_default_constructor() {
    Tvector<int> vector;
    bool expected_result = true;
    bool actual_result =
        vector.get_size() == 0
        && vector.get_deleted() == 0
        && vector.get_capacity() == 0
        && vector.get_data() == nullptr
        && vector.get_states() == nullptr;
    return TestSystem::check(expected_result, actual_result);
}
bool test_2_constructor_with_size() {
    size_t size = 10;
    Tvector<int> vector(size);
    bool expected_result = true;
    bool actual_result =
        vector.get_size() == size
        && vector.get_capacity() == 25
        && vector.get_data() != nullptr
        && vector.get_states() != nullptr
        && vector.get_deleted() == 0;
    return TestSystem::check(expected_result, actual_result);
}
bool test_3_constructor_with_array_and_size() {
    int data[3] = {1,2,3};
    size_t size = 3;
    Tvector<int> vector(data, size);
    bool expected_result = true;
    bool actual_result =
        vector.get_size() == size
        && vector.get_capacity() == 18
        && vector.get_data() != nullptr
        && vector.get_states() != nullptr
        && vector.get_data()[0] == data[0]
        && vector.get_data()[1] == data[1]
        && vector.get_data()[2] == data[2]
        && vector.get_deleted() == 0;
    return TestSystem::check(expected_result, actual_result);
}
bool test_4_copy_constructor() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> old_vector (data, size);
    Tvector<int> new_vector(old_vector);
    bool expected_result = true;
    bool actual_result = old_vector == new_vector;
    return TestSystem::check(expected_result, actual_result);
}
bool test_5_is_empty() {
    Tvector<int> vector;
    bool expected_result = true;
    bool actual_result = vector.is_empty();
    return TestSystem::check(expected_result, actual_result);
}
bool test_6_get_data() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int* data_ptr = data; 
    bool expected_result = true;
    bool different_pointers = data_ptr != vector.get_data();
    bool same_data = 
        data[0] == vector.get_data()[0]
        && data[1] == vector.get_data()[1]
        && data[2] == vector.get_data()[2];
    bool actual_result = different_pointers && same_data;
    return TestSystem::check(expected_result, actual_result);
}
bool test_7_front() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    bool expected_result = vector.get_data()[0];
    bool actual_result = vector.front();
    return TestSystem::check(expected_result, actual_result);
}
bool test_8_back() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    bool expected_result = vector.get_data()[vector.get_size() - 1];
    bool actual_result = vector.back();
    return TestSystem::check(expected_result, actual_result);
}
bool test_9_get_size() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    bool expected_result = size;
    bool actual_result = vector.get_size();
    return TestSystem::check(expected_result, actual_result);
}
bool test_10_get_deleted() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    size_t deleted = 0;
    Tvector<int> vector(data, size);
    bool expected_result = deleted;
    bool actual_result = vector.get_deleted();
    return TestSystem::check(expected_result, actual_result);
}
bool test_11_get_capacity() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    size_t capacity = 18;
    Tvector<int> vector(data, size);
    bool expected_result = capacity;
    bool actual_result = vector.get_capacity();
    return TestSystem::check(expected_result, actual_result);
}
bool test_12_get_begin() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int* expected_result = &(vector.get_data()[0]);
    int* actual_result = vector.begin();
    return TestSystem::check(expected_result, actual_result);
}
bool test_13_get_end() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int* expected_result = &(vector.get_data()[0]) + size;
    int* actual_result = vector.end();
    return TestSystem::check(expected_result, actual_result);
}
bool test_14_сomparison_operator_true() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector1(data, size);
    Tvector<int> vector2(data, size);
    bool expected_result = true;
    bool actual_result = vector1 == vector2;
    return TestSystem::check(expected_result, actual_result);
}
bool test_14_сomparison_operator_false() {
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    bool expected_result = false;
    bool actual_result = vector1 == vector2;
    return TestSystem::check(expected_result, actual_result);
}
bool test_15_not_сomparison_operator_true() {
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    bool expected_result = true;
    bool actual_result = vector1 != vector2;
    return TestSystem::check(expected_result, actual_result);
} 
bool test_15_not_сomparison_operator_false() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector1(data, size);
    Tvector<int> vector2(data, size);
    bool expected_result = false;
    bool actual_result = vector1 != vector2;
    return TestSystem::check(expected_result, actual_result);
}
bool test_16_operator_assign() {
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    Tvector<int> expected_result = true;
    vector1 = vector2;
    Tvector<int> actual_result = vector1 == vector2;
    return TestSystem::check(expected_result, actual_result);
}
bool test_17_operator_staples() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int expected_result = data[1];
    int actual_result = vector[1];
    return TestSystem::check(expected_result, actual_result);
}
bool test_18_at() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int expected_result = data[1];
    int actual_result = vector.at(1);
    return TestSystem::check(expected_result, actual_result);
}
bool test_19_assign() {
    int data[3] = { 1,1,1 };
    size_t size = 3;
    Tvector<int> vector1;
    Tvector<int> vector2(data, size);
    Tvector<int> expected_result = vector2;
    vector1.assign(vector2);
    Tvector<int> actual_result = vector1;
    return TestSystem::check(expected_result, actual_result);
}
bool test_20_clear() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    size_t expected_result = true;
    vector.clear();
    size_t actual_result = vector.get_size() == 0
        && vector.get_deleted() == 0;
    return TestSystem::check(expected_result, actual_result);
}
bool test_21_emplace(){
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.emplace(2, 100);
    int expected_result = 100;
    int actual_result = vector[2];
    return TestSystem::check(expected_result, actual_result);
}
bool test_22_push_front_1() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.push_front(200);
    int expected_result = 200;
    int actual_result = vector[0];
    return TestSystem::check(expected_result, actual_result);
}
bool test_22_push_front_2() {
    int data[1] = { 1 };
    size_t size = 1;
    Tvector<int> vector(data, size);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    vector.push_front(1);
    int expected_result = true;
    int actual_result = vector.get_capacity() == 31
        && vector.get_size() == 17;
    return TestSystem::check(expected_result, actual_result);
}
bool test_23_insert_1() {
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    vector.insert(225, 5);
    int expected_result = 225;
    int actual_result = vector[5];
    return TestSystem::check(expected_result, actual_result);
}
bool test_23_insert_2() {
    size_t size = 10;
    Tvector<int> vector(size);
    vector.insert(225, 5);
    int expected_result = 225;
    int actual_result = vector[5];
    return TestSystem::check(expected_result, actual_result);
}
bool test_23_insert_3() {
    Tvector<int> vector;
    vector.insert(225,5);
    int expected_result = 225;
    int actual_result = vector[5];
    return TestSystem::check(expected_result, actual_result);
}
bool test_23_insert_4() {
    int data[5] = { 1, 2, 3, 4, 5 };
    size_t size = 5;
    Tvector<int> vector(data, size);
    bool expected_result = false;
    bool actual_result = true;
    try {
        vector.insert(225, 5);
    }
    catch (...) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_24_push_back_1() {
    int data[1] = { 1 };
    size_t size = 1;
    Tvector<int> vector(data, size);
    
    vector.push_back(400); 
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(400);
    vector.push_back(300);

    int expected_result = 300;
    int actual_result = vector[16];
    return TestSystem::check(expected_result, actual_result);
}
bool test_24_push_back_2() {
    int data[3] = { 1, 2, 3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.push_back(9);
    int expected_result = 9;
    int actual_result = vector[3];
    return TestSystem::check(expected_result, actual_result);
}
bool test_25_pop_back_1() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.pop_back();
    int expected_result = true;
    int actual_result = vector.get_size() == 2
        && vector[0] == 1
        && vector[1] == 2;
    return TestSystem::check(expected_result, actual_result);
}
bool test_25_pop_back_2() {
    Tvector<int> vector;
    bool expected_result = false;
    bool actual_result = true;
    try {
        vector.pop_back();
    }
    catch (...) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);

}
bool test_26_erase_1() {
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    vector.erase(1);
    vector.erase(1);
    int expected_result = 2;
    int actual_result = vector.get_deleted();
    return TestSystem::check(expected_result, actual_result);
}
bool test_26_erase_2() {
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    vector.erase(1);
    vector.erase(1);
    vector.erase(1);
    bool expected_result = true;
    bool actual_result = vector.get_deleted() == 0
        && vector.get_size() == 12
        && vector.get_capacity() == 27;
    return TestSystem::check(expected_result, actual_result);

}
bool test_26_erase_3() {
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    bool expected_result = false;
    bool actual_result = true;
    try {
        vector.erase(20);
    }
    catch (...) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_27_pop_front_1() {
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.pop_front();
    int expected_result = true;
    int actual_result = vector.get_size() == 2
        && vector[0] == 2
        && vector[1] == 3;
    return TestSystem::check(expected_result, actual_result);
}
bool test_27_pop_front_2() {
    Tvector<int> vector;
    bool expected_result = false;
    bool actual_result = true;
    try {
        vector.pop_front();
    }
    catch (...) {
        actual_result = false;
    }
    return TestSystem::check(expected_result, actual_result);
}
bool test_28_shell_sort() {
    int data[10] = { 1223343, 1546, 8777, 1000, 2, 3, 7, 9, 888, 99 };
    size_t size = 10;
    Tvector<int> vector(data, size);
    int sorted_data[10] = { 2, 3, 7, 9, 99, 888, 1000, 1546, 8777, 1223343 };
    Tvector<int> sorted_vector(sorted_data, size);
    shell_sort(vector);
    Tvector<int> expected_result = sorted_vector;
    Tvector<int> actual_result = vector;
    return TestSystem::check(expected_result, actual_result);
}
bool test_29_find_first() {
    int data[6] = { 1 ,3, 3, 4, 5, 3 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    size_t expected_result = 2;
    size_t actual_result = find_first_element(vector, 3);
    return TestSystem::check(expected_result, actual_result);
}
bool test_30_find_last() {
    int data[6] = { 1 ,3, 3, 4, 5, 3 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    size_t expected_result = 6;
    size_t actual_result = find_last_element(vector, 3);
    return TestSystem::check(expected_result, actual_result);
}
bool test_31_find_count_of_all_suitable_elements() {
    int data[7] = { 1 ,3, 3, 4, 5, 3, 3};
    size_t size = 7;
    Tvector<int> vector(data, size);
    size_t expected_result = 4;
    size_t actual_result = find_count_of_all_suitable_elements(vector, 3);
    return TestSystem::check(expected_result, actual_result);
}

int main() {
    set_color(11, 0);
    std::cout << "TESTS FOR CLASS TVECTOR:" << std::endl;
    set_color(7, 0);
    TestSystem::start_test(test_1_default_constructor, " test_1_default_constructor");
    TestSystem::start_test(test_2_constructor_with_size, " test_2_constructor_with_size");
    TestSystem::start_test(test_3_constructor_with_array_and_size, " test_3_constructor_with_array_and_size");
    TestSystem::start_test(test_4_copy_constructor, " test_4_copy_constructor");
    TestSystem::start_test(test_5_is_empty, " test_5_is_empty");
    TestSystem::start_test(test_6_get_data, " test_6_get_data");
    TestSystem::start_test(test_7_front, " test_7_front");
    TestSystem::start_test(test_8_back, " test_8_back");
    TestSystem::start_test(test_9_get_size, " test_9_get_size");
    TestSystem::start_test(test_10_get_deleted, " test_10_get_deleted");
    TestSystem::start_test(test_11_get_capacity, " test_11_get_capacity");
    TestSystem::start_test(test_12_get_begin, " test_12_get_begin");
    TestSystem::start_test(test_13_get_end, " test_13_get_end");
    TestSystem::start_test(test_14_сomparison_operator_true, " test_14_comparison_operator_true");
    TestSystem::start_test(test_14_сomparison_operator_false, " test_14_comparison_operator_false");
    TestSystem::start_test(test_15_not_сomparison_operator_true, " test_15_not_comparison_operator_true");
    TestSystem::start_test(test_15_not_сomparison_operator_false, " test_15_not_comparison_operator_false");
    TestSystem::start_test(test_16_operator_assign, " test_16_operator_assign");
    TestSystem::start_test(test_17_operator_staples, " test_17_operator_staples");
    TestSystem::start_test(test_18_at, " test_18_at");
    TestSystem::start_test(test_19_assign, " test_19_assign");
    TestSystem::start_test(test_20_clear, " test_20_clear");
    TestSystem::start_test(test_21_emplace, " test_21_emplace");
    TestSystem::start_test(test_22_push_front_1, " test_22_push_front_1");
    TestSystem::start_test(test_22_push_front_2, " test_22_push_front_2");
    TestSystem::start_test(test_23_insert_1, " test_23_insert_1");
    TestSystem::start_test(test_23_insert_2, " test_23_insert_2");
    TestSystem::start_test(test_23_insert_3, " test_23_insert_3");
    TestSystem::start_test(test_23_insert_4, " test_23_insert_4");
    TestSystem::start_test(test_24_push_back_1, " test_24_push_back_1");
    TestSystem::start_test(test_24_push_back_2, " test_24_push_back_2");
    TestSystem::start_test(test_25_pop_back_1, " test_25_pop_back_1");
    TestSystem::start_test(test_25_pop_back_2, " test_25_pop_back_2");
    TestSystem::start_test(test_26_erase_1, " test_26_erase_1");
    TestSystem::start_test(test_26_erase_2, " test_26_erase_2");
    TestSystem::start_test(test_26_erase_3, " test_26_erase_3");
    TestSystem::start_test(test_27_pop_front_1, " test_27_pop_front_1");
    TestSystem::start_test(test_27_pop_front_2, " test_27_pop_front_2");
    TestSystem::start_test(test_28_shell_sort, " test_28_shell_sort");
    TestSystem::start_test(test_29_find_first, " test_29_find_first");
    TestSystem::start_test(test_30_find_last, " test_30_find_last");
    TestSystem::start_test(test_31_find_count_of_all_suitable_elements, " test_31_find_count_of_all_suitable_elements");
    TestSystem::print_final_info();
    system("pause");
    return 0;
}

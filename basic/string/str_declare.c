#include <stdio.h>

int main() {
    // 1. Character array initialized with a string literal (mutable)
    char str1[] = "Hello, world!";
    printf("str1: %s\n", str1);

    // 2. Pointer to string literal (immutable - DO NOT modify)
    const char *str2 = "Hello, world!";
    printf("str2: %s\n", str2);

    // 3. Character array with manual character list (including null terminator)
    char str3[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    printf("str3: %s\n", str3);

    // 4. Pointer initialized to a character array (mutable through str4, not the literal)
    char str4_arr[] = "Hello!";
    char *str4 = str4_arr;
    printf("str4: %s\n", str4);

    // 5. Array of pointers (array of string literals)
    const char *str5[] = {"Apple", "Banana", "Cherry"};
    printf("str5[0]: %s, str5[1]: %s, str5[2]: %s\n", str5[0], str5[1], str5[2]);

    // 6. Character pointer dynamically allocated (using malloc)
    char *str6 = (char *)malloc(20 * sizeof(char));
    if (str6 != NULL) {
        sprintf(str6, "Dynamic string");
        printf("str6: %s\n", str6);
        free(str6);
    }

    // 7. Multidimensional char array (2D array for multiple strings)
    char str7[3][10] = {
        "One",
        "Two",
        "Three"
    };
    printf("str7[0]: %s, str7[1]: %s, str7[2]: %s\n", str7[0], str7[1], str7[2]);

    // 8. Character array without null terminator (Not a proper string)
    char str8[] = {'H', 'i'};
    // printf("str8: %s\n", str8); // ⚠️ Undefined behavior if printed as string

    // 9. Character array with extra space
    char str9[20] = "Short";
    printf("str9: %s\n", str9);

    // 10. String constant assigned to a pointer (immutable)
    const char *str10 = "Immutable string";
    printf("str10: %s\n", str10);

    // 11. Using braces in initialization
    char str11[] = {"Hello from braced init!"};
    printf("str11: %s\n", str11);

    return 0;
}

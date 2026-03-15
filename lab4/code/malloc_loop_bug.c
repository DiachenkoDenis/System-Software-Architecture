int main() {
    int *ptr = NULL;
    for (int i = 0; i < 3; i++) {
        if (!ptr)
            ptr = malloc(sizeof(int));
        *ptr = i;
        printf("Iteration %d value = %d\n", i, *ptr);
        free(ptr);
    }
    return 0;
}

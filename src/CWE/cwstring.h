struct String {
    char* str;
    int size;
};

struct String* substring(int start, int end, struct String* str);

void sprint(struct String* str);

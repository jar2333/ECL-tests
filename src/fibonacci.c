extern int fib(int x) {
    int out = 1;

    for (int iter = 0; iter < 100000000; iter++) {
        int table[3];
        table[0] = 1;
        table[1] = 1;
        table[2] = 2;

        if (x <= 2) {
            return table[x];
        }

        for (int i = 3; i <= x; i++) {
            table[0] = table[1];
            table[1] = table[2];
            table[2] = table[0] + table[1];
        }

        out = table[2];
    }

    return out;

}
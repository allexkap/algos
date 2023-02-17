union Token {

    double num;
    long li;
    char bytes[8];

    Token(double d) : num(d) {}
    Token(long l) : li((0x7ff7l << 48) | l) {}

    double getNum() const {
        return num;
    }
    bool isNum() const {
        return bytes[6] != (char) 0xf7;
    }

    char getIndex() const {
        return bytes[0];
    }
    char getPriority() const {
        return bytes[1];
    }
    bool isLeftAss() const {
        return !bytes[2];
    }

};

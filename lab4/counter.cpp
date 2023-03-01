struct Int {

    int value;
    inline static int asg = 0, cmp = 0;

    Int() : value(0) { }

    Int& operator=(const Int &rhs) {
        ++asg;
        value = rhs.value;
        return *this;
    }
    
    bool operator==(const Int &rhs) const { 
        ++cmp;
        return value == rhs.value;
    }
    bool operator<(const Int &rhs) const { 
        ++cmp;
        return value < rhs.value;
    }
    bool operator>(const Int &rhs)  const { return rhs < *this;     }
    bool operator!=(const Int &rhs) const { return !(*this == rhs); }
    bool operator<=(const Int &rhs) const { return !(rhs < *this);  }
    bool operator>=(const Int &rhs) const { return !(*this < rhs);  }

    template <typename stream>
    friend stream& operator>>(stream&, Int&);
    template <typename stream>
    friend stream& operator<<(stream&, Int&);
};


template <typename stream>
stream& operator>>(stream &in, Int &rhs) {
    in >> rhs.value;
    return in;
}

template <typename stream>
stream& operator<<(stream &out, Int &rhs) {
    out << rhs.value;
    return out;
}

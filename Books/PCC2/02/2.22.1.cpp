p(x);
g(x);
left(x);
right(x);

rotateLeft(y) {
    x = right(y);
    z = p(y);
    if (z != null) {
        if (y == left(z)) left(z) = x;
        else if (y == right(z)) right(z) = x;
    }
    lc = left(x);
    left(x) = y;
    right(y) = lc;
    p(x) = z;
    p(y) = x;
    if (lc != null) p(lc) = y;
}

rotateRight(y) {
    x = left(y);
    z = p(y);
    if (z != null) {
        if (y == left(z)) left(z) = x;
        else if (y == right(z)) right(z) = x;
    }
    rc = right(x);
    right(x) = y;
    left(y) = rc;
    p(x) = z;
    p(y) = x;
    if (rc != null) p(rc) = y;    
}

void splay(x) {
    while (p(x) != null) {
        if (x == left(p(x)) {
            if (g(x) == null) rotateRight(p(x));
            else if (p(x) == left(g(x))) { rotateRight(g(x)); rotateRight(p(x)); }
            else if (p(x) == right(g(x))) { rotateRight(p(x)); rotateLeft(p(x)); }
        } else if (x == right(p(x)) {
            if (g(x) == null) rotateLeft(p(x));
            else if (p(x) == right(g(x))) { rotateLeft(g(x)); rotateLeft(p(x)); }
            else if (p(x) == left(g(x))) {rotateLeft(p(x)); rotateRight(p(x)); }
        }
    }
}

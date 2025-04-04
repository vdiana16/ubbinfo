package org.example.socialnetwork.domain;

import java.util.Objects;

public class Tuple<E1, E2>{
    private E1 first;
    private E2 second;

    public Tuple(E1 first, E2 second){
        this.first = first;
        this.second = second;
    }

    public E1 getFirst() {
        return first;
    }

    public void setFirst(E1 first) {
        this.first = first;
    }

    public E2 getSecond() {
        return second;
    }

    public void setSecond(E2 second) {
        this.second = second;
    }

    @Override
    public String toString() {
        return "Tuple [first=" + first + ", second=" + second + "]";
    }

    @Override
    public int hashCode() {
        return Objects.hash(first, second);
    }

    @Override
    public boolean equals(Object obj) {
        return this.first.equals(((Tuple)obj).first) && this.second.equals(((Tuple)obj).second);
    }
}

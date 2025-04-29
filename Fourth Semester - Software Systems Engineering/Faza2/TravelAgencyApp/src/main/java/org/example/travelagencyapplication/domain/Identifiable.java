package org.example.travelagencyapplication.domain;

import jakarta.persistence.*;

import java.io.Serializable;

@MappedSuperclass
public class Identifiable<ID extends Serializable> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")
    ID id;

    public Identifiable() {
    }

    public Identifiable(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }
}

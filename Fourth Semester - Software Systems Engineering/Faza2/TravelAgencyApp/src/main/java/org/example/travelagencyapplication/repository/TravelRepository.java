package org.example.travelagencyapplication.repository;

import org.example.travelagencyapplication.domain.Travel;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface TravelRepository extends JpaRepository<Travel, Integer> {
    @Query("SELECT t FROM Travel t")
    List<Travel> findAll();
}

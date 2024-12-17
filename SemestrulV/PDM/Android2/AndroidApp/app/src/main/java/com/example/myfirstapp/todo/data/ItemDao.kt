package com.example.myfirstapp.todo.data

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import androidx.room.Update

@Dao
interface ItemDao {
    @Query("SELECT * FROM Item")
    fun getAll(): List<Item>

    @Query("SELECT * FROM Item WHERE _id == :id")
    fun getById(id: String): List<Item>

    @Insert
    fun insert(item: Item)

    @Update
    fun update(item: Item)

    @Query("DELETE FROM Item")
    fun clear()

    @Query("DELETE FROM Item WHERE _id == :id")
    fun deleteById(id:String)
}
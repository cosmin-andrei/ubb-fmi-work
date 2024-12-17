package com.example.myfirstapp.todo.data
import androidx.room.Entity
import androidx.room.PrimaryKey
import com.example.myfirstapp.todo.ui.item.convertDateToString
import java.util.Date

@Entity
data class Item(
    @PrimaryKey val _id: String = "${System.currentTimeMillis()*10000}",
    val title: String = "",
    val description: String = "",
    val date: String = convertDateToString(Date()),
    val participants: Int = 0,
    val status: Boolean = false,
    var requiresCreate: Boolean=false,
    var requiresUpdate: Boolean=false
)
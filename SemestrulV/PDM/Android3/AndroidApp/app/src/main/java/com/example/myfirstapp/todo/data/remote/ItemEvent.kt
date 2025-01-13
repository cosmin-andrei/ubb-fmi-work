package com.example.myfirstapp.todo.data.remote

import com.example.myfirstapp.todo.data.Item

data class Payload(val updatedItem: Item)
data class ItemEvent(val event: String, val payload: Payload)

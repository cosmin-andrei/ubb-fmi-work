package com.example.myfirstapp.todo.data

import android.content.Context
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.Toast
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.core.data.remote.Api
import com.example.myfirstapp.todo.data.remote.ItemEvent
import com.example.myfirstapp.todo.data.remote.ItemService
import com.example.myfirstapp.todo.data.remote.ItemWsClient
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.channels.BufferOverflow
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.callbackFlow
import kotlinx.coroutines.withContext


class ItemRepository(private val itemService: ItemService,
                     private val itemWsClient: ItemWsClient,
                     private val database: ItemDatabase,
                     private val context: Context
) {
    private var items: List<Item> = listOf()


    private var itemsFlow: MutableSharedFlow<Result<List<Item>>> = MutableSharedFlow(
        replay = 1,
        onBufferOverflow = BufferOverflow.DROP_OLDEST
    )

    val itemStream: Flow<Result<List<Item>>> = itemsFlow

    init {
        Log.d(TAG, "init")
    }

    suspend fun refresh() {
        Log.d(TAG, "refresh started")
        try {
            items = itemService.find(authorization = getBearerToken())
            database.itemDao().clear()
            for(item in items) {
                item.requiresUpdate = false
                item.requiresCreate = false
                database.itemDao().insert(item)
            }
            Log.d(TAG, "refresh succeeded")
            itemsFlow.emit(Result.Success(items))
        } catch (e: Exception) {
            Log.d(TAG, "refresh failed", e)
            items  =database.itemDao().getAll()
            itemsFlow.emit(Result.Success(items))
            //itemsFlow.emit(Result.Error(e))
        }
    }

    suspend fun openWsClient() {
        Log.d(TAG, "openWsClient")
        withContext(Dispatchers.IO) {
            getItemEvents().collect {
                Log.d(TAG, "Item event collected $it")
                if (it is Result.Success) {
                    val itemEvent = it.data
                    when (itemEvent.event) {
                        "created" -> handleItemCreated(itemEvent.payload.updatedItem)
                        "updated" -> handleItemUpdated(itemEvent.payload.updatedItem)
                        "deleted" -> handleItemDeleted(itemEvent.payload.updatedItem)
                    }
                }
            }
        }
    }

    suspend fun closeWsClient() {
        Log.d(TAG, "closeWsClient")
        withContext(Dispatchers.IO) {
            itemWsClient.closeSocket()
        }
    }

    private fun getItemEvents(): Flow<Result<ItemEvent>> = callbackFlow {
        Log.d(TAG, "getItemEvents started")
        itemWsClient.openSocket(
            onEvent = {
                Log.d(TAG, "onEvent $it")
                if (it != null) {
                    Log.d(TAG, "onEvent trySend $it")
                    trySend(Result.Success(it))
                }
            },
            onClosed = { close() },
            onFailure = { close() })
        awaitClose { itemWsClient.closeSocket() }
    }

    suspend fun update(item: Item): Item {
        try {
            item.requiresUpdate=false
            Log.d(TAG, "update $item...")
            val updatedItem = itemService.update(authorization = getBearerToken(), item._id, item)
            Log.d(TAG, "update $item succeeded")
            handleItemUpdated(updatedItem)
            return updatedItem
        }
        catch (ex:Exception){
            Log.d(TAG, "failed update $item")
            item.requiresUpdate=true
            handleItemUpdated(item)

            Handler(Looper.getMainLooper()).post {
                Toast.makeText(context, "Server unreachable. Saved locally", Toast.LENGTH_LONG)
                    .show()
            }
            return item
        }
    }

    suspend fun save(item: Item): Item {
        try {
            Log.d(TAG, "save $item...")
            item.requiresCreate=false
            val createdItem = itemService.create(authorization = getBearerToken(), item)
            Log.d(TAG, "save $item succeeded")
            Log.d(TAG, "handle created $createdItem")
            handleItemCreated(createdItem)
            return createdItem
        }
        catch (ex:Exception){
            val createdItem = Item(
                title = item.title,
                description = item.description,
                participants = item.participants,
                status = item.status,
                date = item.date,
                requiresCreate = true,
                requiresUpdate = false
            )
            Log.d(TAG, "failed create on the server $item")
            handleItemCreated(createdItem)

            Handler(Looper.getMainLooper()).post {
                Toast.makeText(context, "Server unreachable. Saved locally", Toast.LENGTH_LONG)
                    .show()
            }
            return createdItem
        }
    }

    private fun handleItemDeleted(item: Item) {
        Log.d(TAG, "handleItemDeleted - todo $item")
    }

    private suspend fun handleItemUpdated(item: Item?) {
        if (item == null) {
            Log.e(TAG, "handleItemUpdated: Item este null.")
            return
        }
        if (item._id == null) {
            Log.e(TAG, "handleItemUpdated: Item._id este null.")
            return
        }

        Log.d(TAG, "handleItemUpdated...: $item")
        items = items.map { if (it._id == item._id) item else it }
        database.itemDao().update(item)
        itemsFlow.emit(Result.Success(items))
    }


    private suspend fun handleItemCreated(item: Item?) {
        Log.d(TAG, "handleItemCreated: Item primit = $item")
        if (item == null) {
            Log.e(TAG, "handleItemCreated: Item este null.")
            return
        }
        if (item._id == null) {
            Log.e(TAG, "handleItemCreated: Item._id este null.")
            return
        }

        Log.d(TAG, "handleItemCreated: Inserăm Item cu ID: ${item._id}")
        if (!items.contains(item)) {
            items = items.plus(item)
            database.itemDao().insert(item)
        }
        itemsFlow.emit(Result.Success(items))
    }


    fun quite_remove(item:Item){
        items = items.minus(item)
        database.itemDao().deleteById(item._id)
    }

    fun setToken(token: String) {
        itemWsClient.authorize(token)
    }

    private fun getBearerToken() = "Bearer ${Api.tokenInterceptor.token}"
}
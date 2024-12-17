package com.example.myfirstapp.todo.ui.item

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.myfirstapp.MyFirstApplication
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.todo.data.Item
import com.example.myfirstapp.todo.data.ItemRepository
import kotlinx.coroutines.launch
import java.util.Date

data class ItemUiState(
    val itemId: String? = null,
    val item: Item = Item(),
    var loadResult: Result<Item>? = null,
    var submitResult: Result<Item>? = null,
)

class ItemViewModel(private val itemId: String?, private val itemRepository: ItemRepository) :
    ViewModel() {

    var uiState: ItemUiState by mutableStateOf(ItemUiState(loadResult = Result.Loading))
        private set

    init {
        Log.d(TAG, "init")
        if (itemId != null) {
            loadItem()
        } else {
            uiState = uiState.copy(loadResult = Result.Success(Item()))
        }
    }

    private fun loadItem() {
        viewModelScope.launch {
            itemRepository.itemStream.collect { result ->
                if (uiState.loadResult !is Result.Loading) {
                    return@collect
                }
                if (result is Result.Success) {
                    val items = result.data
                    val item = items.find { it._id == itemId } ?: Item()
                    uiState = uiState.copy(loadResult = Result.Success(item), item = item)
                } else if (result is Result.Error) {
                    uiState =
                        uiState.copy(loadResult = Result.Error(result.exception))
                }
            }
        }
    }

    fun saveItem(title: String, description: String, participants: Int, status: Boolean, date: Date){
        viewModelScope.launch {
            try{
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.item.copy(
                    title = title,
                    description = description,
                    participants = participants,
                    status = status,
                    date = convertDateToString(date)
                )
                val savedItem: Item = itemRepository.save(item)
                uiState = uiState.copy(submitResult = Result.Success(savedItem))
            }catch (e: Exception){
                Log.d(TAG, "saveOrUpdateItem failed")
                uiState = uiState.copy(submitResult = Result.Error(e))
            }
        }
    }

    fun UpdateItem(title: String, description: String, participants: Int, status: Boolean, date: Date) {
        viewModelScope.launch {
            Log.d(TAG, "update item!!!")
            try {
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.item.copy(
                    title = title,
                    description = description,
                    participants = participants,
                    status = status,
                    date = convertDateToString(date)
                )
                val updatedItem: Item = itemRepository.update(item)
                Log.d(TAG, "UpdateItem succeeded")
                uiState = uiState.copy(submitResult = Result.Success(updatedItem))
            } catch (e: Exception) {
                Log.d(TAG, "saveOrUpdateItem failed")
                uiState = uiState.copy(submitResult = Result.Error(e))
            }
        }
    }

    companion object {
        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                ItemViewModel(itemId, app.container.itemRepository)
            }
        }
    }
}

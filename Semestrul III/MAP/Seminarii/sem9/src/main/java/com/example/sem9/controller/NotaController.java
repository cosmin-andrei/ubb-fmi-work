package com.example.sem9.controller;

import com.example.sem9.domain.NotaDto;
import com.example.sem9.service.ServiceManager;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;


import java.util.List;
import java.util.Objects;
import java.util.function.DoubleBinaryOperator;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class NotaController {

    ObservableList<NotaDto> modelGrade = FXCollections.observableArrayList();
    List<String> modelTema;
    private ServiceManager service;


    @FXML
    TableColumn<NotaDto, String> tableColumnName;
    @FXML
    TableColumn<NotaDto, String> tableColumnTema;
    @FXML
    TableColumn<NotaDto, Double> tableColumnNota;
    @FXML
    TableView<NotaDto> tableViewNote;
    //----------------------end TableView fx:id----------------

    @FXML
    TextField textFieldName;
    @FXML
    TextField textFieldTema;
    @FXML
    TextField textFieldNota;

    @FXML
    ComboBox<String> comboBoxTeme;

    @FXML
    public void initialize() {
        tableColumnName.setCellValueFactory(new PropertyValueFactory<NotaDto, String>("studentName"));
        tableColumnTema.setCellValueFactory(new PropertyValueFactory<NotaDto, String>("temaId"));
        tableColumnNota.setCellValueFactory(new PropertyValueFactory<NotaDto, Double>("nota"));

        tableViewNote.setItems(modelGrade);

        //atunci cand se modifica ceva, se notif listener (observatorii)
        textFieldName.textProperty().addListener(o -> handleFilter());
        textFieldTema.textProperty().addListener(o -> handleFilter());
        textFieldNota.textProperty().addListener(o -> handleFilter());

//        comboBoxTeme.getSelectionModel().selectedItemProperty().addListener(
//                (x,y,z)->handleFilter()
//        );


    }

    private List<NotaDto> getNotaDTOList() {
        return service.findAllGrades()
                .stream()
                .map(n -> new NotaDto(n.getStudent().getName(), n.getTema().getId(), n.getValue(), n.getProfesor()))
                .collect(Collectors.toList());
    }

    private void handleFilter() {

        String name = textFieldName.getText();
        String tema = textFieldTema.getText();
//        if(textFieldNota.getText() != null){
//            Double nota = Double.valueOf(textFieldNota.getText());
//        }
        String nota = textFieldNota.getText();

        List<NotaDto> multipleFilter = getNotaDTOList();
        if(!name.isEmpty()){
            multipleFilter=multipleFilter.stream()
                    .filter(o->o.getStudentName().startsWith(name))
                    .toList();
        }

        if(!tema.isEmpty()){
            multipleFilter=multipleFilter.stream()
                    .filter(o->o.getTemaId().startsWith(tema))
                    .toList();
        }

        if(!nota.isEmpty()){
            multipleFilter=multipleFilter.stream()
                    .filter(o->o.getNota()>Double.parseDouble(nota))
                    .toList();
        }

//        String selection = comboBoxTeme.getSelectionModel().getSelectedItem();
//        List<NotaDto> all = getNotaDTOList()
//                        .stream()
//                        .filter(notaDto -> notaDto.getTemaId().equals(selection))
//                        .toList();
//
        modelGrade.setAll(multipleFilter);
    }


    public void setService(ServiceManager service) {
        this.service = service;
        modelGrade.setAll(getNotaDTOList());
        modelTema = service.findAllHomeWorks()
                .stream()
                .map(x -> x.getId())
                .collect(Collectors.toList());
//        comboBoxTeme.getItems().setAll(modelTema);
//        comboBoxTeme.getSelectionModel().selectFirst();
    }
}

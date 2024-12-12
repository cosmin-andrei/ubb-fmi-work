import React, { memo } from "react";
import { IonItem, IonLabel, IonNote } from "@ionic/react";
import { getLogger } from "../core";
import { ProjectProps } from "./ProjectProps";
import styles from "./styles.module.css";

interface ProjectPropsExtended extends ProjectProps {
    onEdit: (_id?: string) => void;
}

const ProjectComponent: React.FC<ProjectPropsExtended> = ({
  _id,
  title,
  description,
  date,
  participants,
  status,
  isNotSaved,
  onEdit,
}) => (
  <IonItem
    style={{ color: isNotSaved ? "red" : undefined, height: "15vw" }}
    onClick={() => onEdit(_id)}
  >
    <IonNote slot="start" style={{ marginRight: "1em" }}>
      {status ? "Active" : "Inactive"}
    </IonNote>
    <IonLabel>
      <h2>
        <b>{title}</b>
      </h2>
      <p>{description}</p>
      <p>
        <i>Date:</i>{" "}
        {date ? new Date(date).toISOString().split("T")[0] : "(Invalid date)"}
      </p>
      <p>
        <i>Participants:</i> {participants}
      </p>
    </IonLabel>
  </IonItem>
);

export default memo(ProjectComponent);

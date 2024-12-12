export interface ProjectProps {
    _id?: string;
    title: string;
    description: string;
    date: Date;
    participants: number;
    status: boolean;
    isNotSaved: boolean;
    photo?: string;
    lat?: number; 
    lng?: number;
}

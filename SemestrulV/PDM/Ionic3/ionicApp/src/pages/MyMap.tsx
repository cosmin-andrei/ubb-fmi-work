import React, { useState, useEffect, useRef } from "react";
import { GoogleMap } from '@capacitor/google-maps';
import { mapsApiKey } from './mapsApiKey';

interface MyMapProps {
  lat?: number;
  lng?: number;
  onCoordsChanged: (lat: number, lng: number) => void;
}

export const MyMap: React.FC<MyMapProps> = ({ lat, lng, onCoordsChanged }) => {
  const mapRef = useRef<HTMLElement>();
  let newMap: GoogleMap;
  let markerId: string;

  const [latitude, setLatitude] = useState<number | undefined>(lat);
  const [longitude, setLongitude] = useState<number | undefined>(lng);
  const [mapLoaded, setMapLoaded] = useState<boolean>(false);

  console.log(`init lat = ${latitude}`);

  useEffect(() => {
    if (!mapLoaded) {
      createMap();
    } else if (latitude && longitude) {
      addMarker(latitude, longitude);
    }
  }, [lat, lng, mapLoaded]);

  async function createMap() {
    if (!mapRef.current) {
      console.error("Map element not found");
      return;
    }
  
    console.log("Creating map...");
    newMap = await GoogleMap.create({
      id: 'my-cool-map',
      element: mapRef.current,
      apiKey: mapsApiKey,
      config: {
        center: {
          lat: latitude || 0,
          lng: longitude || 0,
        },
        zoom: 8,
      },
    });
  
    console.log("Map created");
  
    // Adaugă markerul inițial
    if (latitude !== undefined && longitude !== undefined) {
      console.log("Adding initial marker");
      markerId = await newMap.addMarker({
        coordinate: {
          lat: latitude,
          lng: longitude,
        },
      });
    }
  
    // Ascultă evenimentele de click pe hartă
    await newMap.setOnMapClickListener(async (event)=>{                        
      console.log(`LL ${event.latitude} ${event.longitude}`); 
      newMap.removeMarker(markerId);
      markerId = await newMap.addMarker({
          coordinate: {
          lat: event.latitude,
          lng: event.longitude
          }                                
      });
      onCoordsChanged(event.latitude, event.longitude);               
  });            
  
    setMapLoaded(true);
  }
  
  

  async function addMarker(lat: number, lng: number) {
    if (newMap) {
      if (markerId) {
        await newMap.removeMarker(markerId);
      }
      markerId = await newMap.addMarker({
        coordinate: { lat, lng }
      });
    }
  }

  return (
    <div className="component-wrapper">
      <capacitor-google-map
        ref={mapRef}
        style={{
          display: 'inline-block',
          width: "100%",
          height: 400
        }}
      ></capacitor-google-map>
    </div>
  );
};

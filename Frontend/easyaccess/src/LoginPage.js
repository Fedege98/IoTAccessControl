import React, { useState } from "react";
import './App.css';
import icon from "./icon1.svg"

function LoginPage() {

    const [email, setEmail] = useState("")
    const [password, setPassword] = useState("")

    return (
        <div style={{ display: "flex", flexDirection: "column", width:"100%" }}>
            <header className="App-header">
                <div style={{ }}>
                    <img src={icon} className="App-logo"/>
                    <div>
                        <a className="Pages" href="#">Home</a>
                        <a className="Pages" href="#">Login/Register</a>
                        <a className="Pages" href="#">Log Entrances</a>
                    </div>
                </div>


            </header>
            <div className="loginDiv">
                <input className="InputField" onChange={setEmail}autoFocus={true}></input>
                <input className="InputField" onChange={setPassword}></input>
                <div className="ButtonsinLogpage">
                    <button className="Buttons">Register</button>
                    <button className="Buttons">Login</button>
                </div>
            </div>
        </div>
    );

} export default LoginPage

/*
background-color: #aa21ff;
  width: 300px;
  min-height: 300px;
  padding: 5px;
  display: flex;
  justify-content: center;
  align-items: center;
  
  position the div in center 
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
   */
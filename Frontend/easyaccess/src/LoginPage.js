import React, { useState } from "react";
import './App.css';
import icon from "./icon1.svg"


function LoginPage() {

    const [email, setEmail] = useState("")
    const [password, setPassword] = useState("")
    const [showSignUp, setShowSignUp] = useState(true)
    const [showSignIn, setShowSignIn] = useState(false)

    return (
        <div style={{ display: "flex", flexDirection: "column", width: "100%" }}>

            <header class="d-flex flex-wrap align-items-center justify-content-center justify-content-md-between py-3 mb-4 border-bottom">
                <div className="Icon">
                    <img className="Icon" src={icon}/>
                </div>
                <ul class="nav col-12 col-md-auto mb-2 justify-content-center mb-md-0">
                    <li id="NavLinks"><a href="#" class="nav-link px-2 link-secondary">Home</a></li>
                    <li id="NavLinks"><a href="#" class="nav-link px-2">Log Entrances</a></li>
                </ul>

                <div class="col-md-3 text-end">
                    <button type="button" class="btn btn-outline-primary me-2">Login</button>
                    <button type="button" class="btn btn-primary">Sign-up</button>
                </div>
            </header>


            <div class="modal-content rounded-4 shadow" id="formforsign">
                <div class="modal-header p-5 pb-4 border-bottom-0">
                    <h1 class="fw-bold mb-0 fs-2">Sign up for the access</h1>
                </div>

                <div class="modal-body p-5 pt-0">
                    <form class="">
                        <div class="form-floating mb-3">
                            <input onChange={setEmail} type="email" class="form-control rounded-3" id="floatingInput" placeholder="name@example.com" />
                            <label for="floatingInput">Email address</label>
                        </div>
                        <div class="form-floating mb-3">
                            <input onChange={setPassword} type="password" class="form-control rounded-3" id="floatingPassword" placeholder="Password" />
                            <label for="floatingPassword">Password</label>
                        </div>
                        <button class="w-100 mb-2 btn btn-lg rounded-3 btn-primary" type="submit">Sign up</button>
                        <small class="text-body-secondary">By clicking Sign up, you agree to the terms of use.</small>
                        <hr class="my-4"></hr>
                    </form>
                </div>
            </div>

            <div class="container">
                <footer class="d-flex flex-wrap justify-content-between align-items-center py-3 my-4 border-top">
                    <div class="col-md-4 d-flex align-items-center">

                        <span class="mb-3 mb-md-0 text-body-secondary">© 2023 Company, Inc</span>
                    </div>

                    <ul class="nav col-md-4 justify-content-end list-unstyled d-flex">
                        <li class="ms-3"><a class="text-body-secondary" href="#"></a></li>
                        <li class="ms-3"><a class="text-body-secondary" href="#"></a></li>
                        <li class="ms-3"><a class="text-body-secondary" href="#"></a></li>
                    </ul>
                </footer>
            </div>
        </div>
    );

} export default LoginPage
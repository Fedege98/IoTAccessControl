Progetto API per la Gestione degli Accessi 🚀
Descrizione 📚

Questo progetto implementa una soluzione per gestire l'accesso ad un edificio universitario tramite un tastierino numerico fisico. L'API riceve un codice generato da un tastierino numerico tramite un gateway IoT. Questo codice viene visualizzato all'utente tramite una web app. L'utente inserisce il codice nella web app, che a sua volta genera un nuovo codice. Se l'utente inserisce il nuovo codice nel tastierino numerico, la porta dell'edificio si apre.

L'hardware consiste in tastierini numerici fisici situati in più edifici di un campus universitario e un Raspberry Pi che funge da gateway IoT. Il gateway IoT è registrato come dispositivo su un IoT Hub Azure, che è utilizzato da un programma backend.

I dati degli utenti e le informazioni sugli edifici a cui possono accedere sono memorizzati in un database Azure SQL. 🗃️

Il database è costituito da tre tabelle:

    Users: Contiene le informazioni sugli utenti.
    Buildings: Contiene le informazioni sugli edifici.
    UsersBuildings: Una tabella di associazione che mappa quali utenti possono accedere a quali edifici.
    AccessLog: registrazione accessi all'edificio.
    Device: registrazione dei devices.

Struttura del codice 📁

Il codice è suddiviso in cartelle, ognuna di esse simula un componente del progetto.

Futuri miglioramenti 🌈
Il progetto potrebbe essere migliorato in diversi modi, ad esempio aggiungendo la gestione degli errori, un'interfaccia utente più sofisticata, e rendendo l'API più sicura.

Contribuire al progetto 👥
Le pull request sono le benvenute. Per modifiche importanti, aprire prima un problema per discutere cosa si vorrebbe cambiare. Assicurarsi di aggiornare i test come appropriato.
Licenza 📝

MIT

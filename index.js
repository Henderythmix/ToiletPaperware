const { exec } = require("child_process");

const express = require('express');
const app = express();
const port = 3000;

app.use("/", express.static('static'));

app.get("/RollsLeft", (req, res) => {
    res.sendFile("rollcount.txt", {root: __dirname});
});

app.get("/BackendCheck", (req, res) => {
    exec("ps | grep backend; echo $?", (error, stdout, stderr) => {
        if (stdout == "1") {
            res.send("Requires Maintenance");
            return 1;
        }
        res.send("Good");
        return 0;
    });
});

app.get("/RestartBackend", (req, res) => {
    exec("./bin/backend & disown", (error, stdout, stderr) => {
        if (error) {
            res.send("Hardware Restart Failed");
            return 1;
        }
        res.send("Restart Successful");
        return 0;
    })
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`);
});
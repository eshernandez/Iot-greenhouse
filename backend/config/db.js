const fastifyPlugin = require('fastify-plugin')
const mongoose = require('mongoose')
//Connect to DB
async function dbConnector(fastify, options) {
    try {
        const url = "mongodb://127.0.0.1:27017/database-server-iot"
        const db = await mongoose
        .connect(url, {
            useUnifiedTopology: true,
            useNewUrlParser: true
        })
        console.log("Database is connected")
        fastify.decorate('mongo', db)
    } catch(err){
        console.error(err);
    }
}

module.exports = fastifyPlugin(dbConnector)

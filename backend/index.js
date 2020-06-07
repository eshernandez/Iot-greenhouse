const fastify = require('fastify')
const db = require("./config/db")
const routes = require("./routes/routes")
const boom = require('boom')//TODO@Santiago: implement boom here!
const request = require('request');
const http = require('http');
const Iot = require("./config/model.js")
const PORT = process.env.PORT || 3300
const app = fastify({
    logger:true, 
    trustProxy: true
})

// midleware
app.register(db)
app.register(require('fastify-cors'))
//TODO@Santiago: crate mixing whit this function and add data save in mongo !
// app.register(async ()=> {
//     setInterval(() => {
//         console.log("xxx");
        
//     }, 2000);
// })
// app.register( async function(){
//     setInterval(async function() {
        
//         // await http.get('http://192.168.0.15/env', (resp) => {http://186.87.251.184/env
//         await http.get('http://186.87.251.184/env', (resp) => {
//             let data = '';
//             // Un fragmento de datos ha sido recibido.
//             resp.on('data', (chunk) => {
//                 data += chunk;
//                 // console.log(JSON.parse(data));
//             });
//             // TODO@Santiago: create minxing with chunk for save mongo
//             resp.on('end', async () => {
//                 // console.log(JSON.parse(data));
//                 try {
//                     // let newposts=[];
//                     datos=JSON.parse(data)
//                     datos.forEach( async function( item ){
//                         let info = new Iot(item);
//                         let log= await info.save();
//                         console.log(log);
                        
//                     });

//                     //TODO@santiago: add message of data return of info.save 
//                     // return {
//                         // status: 'created',
//                         // data: list(req),
//                         // rowStatuses: rowStatuses
//                     // }
//                 } catch (err) {
//                     throw boom.boomify(err)
//                 }
//               });
//     }).on("error", (err) => {
//       console.log("Error: " + err.message);
//     });
//     }, 10000);
// })

// Declare routes
routes.forEach((route, index) => {
    app.route(route)
})
app.get("/",async ()=>{
    return {
        Message: "Fastify is on Fire"
    }
})

// Function to run the server 
const start= async ()=>{
    try {
        await app.listen(PORT,'0.0.0.0')
        app.log.info(`Server listening on ${app.server.address().port} && ${app.server.address().host}` )
    } catch (err){
        app.log.error(err)
        process.exit(1)
    }
}

start()
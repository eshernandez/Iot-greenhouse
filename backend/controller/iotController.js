const boom = require('boom')
const Iot = require("../config/model.js")
// const requestServer = require("../requets/requets")
const request = require('request');

// get all post in api iot
exports.getPostServeIot = async (req, reply) => {
    try {
        let data = await request("http://186.87.251.184/env", function(err, res, body) {
        // console.log(body);    
        })
        return data
    } catch (err) {
        throw boom.boomify(err)
    }
}
// save post if api iot
exports.savePostServeIot = async (req, reply) => {
    try {
        let data = await request("http://186.87.251.184/env", function(err, res, body) {
        console.log(body);    
        })
        return data
    } catch (err) {
        throw boom.boomify(err)
    }
}
// get all post 
exports.getAllPost = async (req, reply) => {
    try {
        let posts = await Iot.find();
        return posts;
    } catch (err) {
        throw boom.boomify(err)
    }
}
// get single post by id 
exports.getSinglePost = async (req, reply) => {
    try {
        const id = req.params.id
        let post = await Iot.findById(id);
        return post
    } catch (err) {
        throw boom.boomify(err)
    }
}
exports.addNewPost = async (req, reply) => {
    try {
        let post = new Iot(req.body);
        let newpost = await post.save();
        return newpost
    } catch (err) {
        throw boom.boomify(err)
    }
}
exports.addMultipleNewPost = async (req, reply) => {
    try {
        let newposts=[];
        let data= req.body;
        data.forEach( async function( item ){
            let info = new Iot(item);
            await info.save();
            // messagesForWrapper.forEach(m => messages.push(m))
        });
        //TODO@santiago: add message of data return of info.save 
        return {
            status: 'created',
            // data: list(req),
            // rowStatuses: rowStatuses
        }
    } catch (err) {
        throw boom.boomify(err)
    }
}

exports.updatePost = async (req, reply) => {
    try {
        const id = req.params.id
        let result = await Iot.findByIdAndUpdate(id, req.body, {
            new: true
        });
        return result
    } catch (err) {
        throw boom.boomify(err)
    }
}
exports.deletePost = async (req, reply) => {
    try {
        const id = req.params.id
        let result = await Iot.findByIdAndDelete(
            id
        );
        return {Message:"Post Deleted"}
    } catch (err) {
        throw boom.boomify(err)
    }
}
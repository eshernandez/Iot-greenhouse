const mongoose = require('mongoose')
const autoIncrement = require('mongoose-auto-increment');
const postSchema = new mongoose.Schema({
    type: {
        type: String,
        required: true
    },
    value: {
        type: Number,
        required: true
    },
    unit: {
        type: String,
        required: true
    },
    // author: {
    //     type: String,
    //     required: true
    // }
}, {
    timestamps: true
})

autoIncrement.initialize(mongoose.connection);
postSchema.plugin(autoIncrement.plugin, 'POST'); 
module.exports = mongoose.model('POST', postSchema)
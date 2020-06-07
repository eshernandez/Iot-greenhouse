const iotController = require('../controller/iotController');
const routes = [
    // {
    //     method: 'GET',
    //     url: '/',
    //     handler: (req, res)=>{
    //         return "hi"
    //     }
    // },
    {
        method: 'GET',
        url: '/api/postsServerIot',
        handler: iotController.getPostServeIot
    },
    {
        method: 'GET',
        url: '/api/posts',
        handler: iotController.getAllPost
    },
    {
        method: 'GET',
        url: '/api/post/:id',
        handler: iotController.getSinglePost
    },
    {
        method: 'POST',
        url: '/api/post',
        handler: iotController.addNewPost,
    },
    {
        method: 'POST',
        url: '/api/multiple-post',
        handler: iotController.addMultipleNewPost,
    },
    {
        method: 'PUT',
        url: '/api/post/:id',
        handler: iotController.updatePost
    },
    {
        method: 'DELETE',
        url: '/api/post/:id',
        handler: iotController.deletePost
    }
]
module.exports = routes
module.exports = function (RED) {




    function ledControllerNode(config) {
        RED.nodes.createNode(this, config);
        //Node Specific Code goes here
        var node = this;
        node.on('input', function (msg) {
            //receive message
            //            var MSG_SIZE = 8
            //            var tx_msg = new Uint8Array(MSG_SIZE);
            //            tx_msg[0] =  msg.channel;
            //            tx_msg[1] = msg.mode;
            //            tx_msg[2] = msg.colour;
            //            tx_msg[3] = msg.brightness;
            //            tx_msg[4] = msg.period && 0xFF000000>>24;
            //            tx_msg[5] = msg.period && 0x00FF0000>>16;
            //            tx_msg[6] = msg.period && 0x0000FF00>>8;
            //            tx_msg[7] = msg.period && 0x000000FF;


            msg.payload = msg.payload.toLowerCase();
            node.send(msg);
        });
    }
    RED.nodes.registerType("led-controller", ledControllerNode);
}
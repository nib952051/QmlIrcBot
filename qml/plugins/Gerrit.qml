/*
 * Copyright (C) 2008-2015 The Communi Project
 * and nib952051@gmail.com
 *
 * This example is free, and not covered by the BSD license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

import QtQml 2.0

QtObject {

    property Communi communi    // injected

    property Connections __connection: Connections {
        target: communi.model.connection
        onMessageReceived: {
            if (message.content) {
                var target = message.private ? message.nick : message.target
                console.log(target, message.content)

                __utils.processJiraMessage(target, message.content)
                __utils.processGerritMessage(target, message.content)

            }
        }
    }

    property QtObject __utils: QtObject {
        //! https://github.com/ec1oud/qtquick-trello/blob/master/main.qml
        function getAsPlainText(url, callback) {
            var request = new XMLHttpRequest()
            request.open('GET', url)
            request.onreadystatechange = function(event) {
                if (request.readyState === XMLHttpRequest.DONE) {
                    callback(request.responseText)
                }
            }
            request.send()
        }


        function processJiraMessage(target, content) {
            var res = content.match(/(QTCREATORBUG|QTBUG)-(\d+)/)
            if (res !== null) {
                var issueId = res[1] + '-' + res[2]
                var uri = 'https://bugreports.qt.io/rest/api/latest/issue/' + issueId

                console.log("Jira.Im going to inspect:", uri)
                getAsPlainText(uri, function(ptext) {
                    try {
                        var json = JSON.parse(ptext)
                        var msg = json.fields.summary + " https://bugreports.qt.io/browse/" + issueId
                        communi.model.connection.sendCommand(communi.command.createMessage(target, msg))
                    } catch(err) {
                        console.log("Jira.error:", err, ptext)
                    }
                })
            }
        }

        function processGerritMessage(target, content) {
            var res = content.match(/(I[0-9a-f]{40})/)
            if (res !== null) {
                var uri ='https://codereview.qt-project.org/changes/' + res[1]
                console.log("Gerrit.Im going to inspect:", uri)

                getAsPlainText(uri, function(ptext) {
                    try {
                        var json = JSON.parse(ptext.substring(5))
                        communi.model.connection.sendCommand(communi.command.createMessage(target, json.subject + " status=" + json.status))
                    } catch(err) {
                        console.log("Gerrit.error:", err, ptext)
                    }
                })
            }
        }

    }
}

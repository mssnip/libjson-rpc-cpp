/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    rpcprotocolserver.h
 * @date    31.12.2012
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#ifndef JSONRPC_CPP_RPCPROTOCOLSERVER_H_
#define JSONRPC_CPP_RPCPROTOCOLSERVER_H_

#include <string>
#include <vector>
#include <map>

#include <jsonrpc/common/specificationparser.h>
#include "abstractrequesthandler.h"

#define KEY_REQUEST_METHODNAME  "method"
#define KEY_REQUEST_VERSION     "jsonrpc"
#define KEY_REQUEST_ID          "id"
#define KEY_REQUEST_PARAMETERS  "params"
#define KEY_RESPONSE_ERROR      "error"
#define KEY_RESPONSE_RESULT     "result"
#define KEY_AUTHENTICATION      "auth"
#define JSON_RPC_VERSION        "2.0"

namespace jsonrpc
{
    class RpcProtocolServer
    {
        public:
            RpcProtocolServer(AbstractRequestHandler &requestHandler, std::vector<Procedure> &procedures);
            RpcProtocolServer(AbstractRequestHandler &requestHandler);

            virtual ~RpcProtocolServer();

            /**
             * This is the key feature of this class, it deals with the JSON-RPC 2.0 protocol.
             *  @param request - holds (hopefully) a valid JSON-Request Object.
             *  @param retValue a reference to string object which will hold the response after this method;
             */
            void HandleRequest(const std::string& request, std::string& retValue);

            /**
             * @brief addMethod adds a new method to the RpcProtocolServer. The added Procedure object is copied internally.
             * @param procedure
             */
            void AddProcedure(Procedure& procedure);

            /**
             * @brief AddProcedure
             * @param procedure the pointer provided as parameter here will be deleted by the RpcProtocolServer destructor.
             */
            void AddProcedure(Procedure* procedure);


        private:

            void HandleSingleRequest(Json::Value& request, Json::Value& response);
            void HandleBatchRequest(Json::Value& requests, Json::Value& response);

            int ValidateRequest(const Json::Value &val);

            /**
             * @pre the request must be a valid request
             * @param request - the request Object compliant to Json-RPC 2.0
             * @param retValue - a reference to an object which will hold the returnValue afterwards.
             *
             * after calling this method, the requested Method will be executed. It is important, that this method only gets called once per request.
             */
            void ProcessRequest(const Json::Value &request,
                    Json::Value &retValue);

            /**
             * This map holds all procedures. The string holds the name of each procedure.
             */
            std::map<std::string, Procedure*> procedures;
            AbstractRequestHandler &requestHandler;

    };

} /* namespace jsonrpc */
#endif /* JSONRPC_CPP_RPCPROTOCOLSERVER_H_ */

#include "keriocurlcore.h"

KerioCurlCore::KerioCurlCore(QObject *parent) : QObject(parent)
{

}

bool KerioCurlCore::read_cookies(CURL* curl)
{
    auto check = false;
    CURLcode res;


    QFile file("cookies.txt");
    struct curl_slist* cookies;
    struct curl_slist* nc;
    int i;

    res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
    if (res != CURLE_OK)
    {
        std::cout << curl_easy_strerror(res);
        check = false;
    } else {
        QFile::remove("cookies.txt");
        if (file.open(QIODevice::ReadWrite))
        {
            nc = cookies;
            i = 1;
            QTextStream in(&file);
            while (nc)
            {
                //printf("[%d]: %s\n", i, nc->data);
                in << nc->data;
                in << "\n";
                nc = nc->next;
                i++;
            }
            file.close();
            if (i == 1)
            {
                std::cout << "nothing in cookies!" << std::endl;
            }

            curl_slist_free_all(cookies);

        } else {
            check = false;
        }
    }
    return check;
}

size_t KerioCurlCore::writer(char* contents, size_t nmemb, size_t size, std::string *data)
{
    data->append(contents, nmemb * size);
    return nmemb * size;
}

std::string KerioCurlCore::prepare(KerioMethod method, QHash<KerioParams, QVariant> params, JsonRpcEngine* jrpc)
{
    std::string _prepareString = jrpc->generate(method, params);
    return _prepareString;
}

std::string KerioCurlCore::setUrl(std::string host, int port, std::string target)
{
    return "https://" + host + ":" + std::to_string(port) + target;
}

QHash<QString, QVariant> KerioCurlCore::perform(KerioMethod method, QHash<KerioParams, QVariant> params, std::string host, int port, std::string target)
{
    JsonRpcEngine* j_engine = new JsonRpcEngine();
    CURL* curl_core;

    QHash<QString, QVariant> response;
    QFile file("cookies.txt");
    CURLcode perf;
    struct curl_slist* headers = nullptr;

    std::string x_token = "";
    std::string global_url = setUrl(host, port, target);
    std::string ex_data;
    std::string post_request = j_engine->generate(method, params);
    if (params[Token] != NULL)
    {
        x_token.clear();
        x_token = params[Token].toString().toStdString();
    } else {
        x_token.clear();
    }
    if (post_request != "")
    {
        ex_data.clear();
        file.open(QIODevice::ReadWrite);
        curl_global_init(CURL_GLOBAL_ALL);

        headers = curl_slist_append(headers, "Accept: application/json-rpc");
        headers = curl_slist_append(headers, "Content-Type: application/json-rpc");
        headers = curl_slist_append(headers, "User-Agent: King Anthony");
        headers = curl_slist_append(headers, "Host: ats.550550.ru:4021");
        headers = curl_slist_append(headers, "Connection: close");

        if (x_token != "")
        {

            std::string _session = "Cookie: ";
            struct curl_slist* cookies = nullptr;
            std::string _token = "X-Token: "+x_token;
            headers = curl_slist_append(headers, _token.c_str());


            QTextStream out(&file);
            while (!out.atEnd())
            {
                QString line = out.readLine();
                _session = line.toStdString();
                cookies = curl_slist_append(cookies, _session.c_str());
            }
        } else {
        }
        curl_core = curl_easy_init();
        if (curl_core)
        {
            curl_easy_setopt(curl_core, CURLOPT_URL, global_url.c_str());
            curl_easy_setopt(curl_core, CURLOPT_NOSIGNAL, 1L);
            curl_easy_setopt(curl_core, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl_core, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl_core, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl_core, CURLOPT_COOKIEFILE, "cookies.txt");
            curl_easy_setopt(curl_core, CURLOPT_COOKIEJAR, "cookies.txt");
            curl_easy_setopt(curl_core, CURLOPT_POST, 1L);
            curl_easy_setopt(curl_core, CURLOPT_POSTFIELDSIZE, post_request.size());
            curl_easy_setopt(curl_core, CURLOPT_POSTFIELDS, post_request.c_str());
            curl_easy_setopt(curl_core, CURLOPT_WRITEFUNCTION, writer);
            curl_easy_setopt(curl_core, CURLOPT_WRITEDATA, &ex_data);
            //curl_easy_setopt(curlCore, CURLOPT_VERBOSE, 1L);
            perf = curl_easy_perform(curl_core);
            if (perf == CURLE_OK)
            {
                //std::cout << ex_data << std::endl;
                response = j_engine->parse(QString::fromStdString(ex_data));
                read_cookies(curl_core);
                curl_easy_cleanup(curl_core);
            }
        }
        //file.close();
        curl_slist_free_all(headers);
        curl_global_cleanup();
        return response;
    } else {
        response.clear();
        response["Failed"] = 1;
        return response;
    }
}

//
//  HTTPRequest
//

#include"SQLite.h"
#include <HTTPRequest.hpp>
#include<json.hpp>

using json = nlohmann::json;

string GetAuthor(json object,const int& DocIndexx)
{
	string authors_str;
	int author_elements = object["response"]["docs"][DocIndexx]["author_display"].size();
	for (int i = 0; i < author_elements - 1; i++)
	{

		authors_str += to_string(object["response"]["docs"][0]["author_display"][i]) + ",";
		//cout << test << endl;

	}
	authors_str += to_string(object["response"]["docs"][0]["author_display"][author_elements - 1]);
	//cout << endl << test;
	return authors_str;
}

string GetAbstract(json object, const int& DocIndexx)
{
	string abstract_str;
	int abstract_elements = object["response"]["docs"][DocIndexx]["abstract"].size();
	for (int i = 0; i < abstract_elements - 1; i++)
	{

		abstract_str += to_string(object["response"]["docs"][0]["abstract"][i]) + ",";
		//cout << test << endl;

	}
	abstract_str += to_string(object["response"]["docs"][0]["abstract"][abstract_elements - 1]);
	//cout << endl << test;
	return abstract_str;
}

int main(int argc, const char* argv[])
{
	
	
	
	try
	{
		//get API
		http::Request request1{ "http://api.plos.org/search?q=title:DNA" };
		
		const auto response1 = request1.send("GET");
		//cout << std::string{ response1.body.begin(), response1.body.end() } << endl;
		
		//Parse => create json object
		auto text = (string{ response1.body.begin(), response1.body.end() });
		json object = json::parse(text);
		//cout <<setw(4)<< json_object;

		//Open database
		string dataFile;
		cout << "Enter your data file: ";
		fflush(stdin);
		getline(cin, dataFile);

		Database data(dataFile);
		
		//Create table
		data.CreateTable();

		//number of Json "docs"
		auto elements = object["response"]["docs"].size();
		cout << elements << endl;
		
		
		//object["response"]["docs"][i]["id"]

		//Create all Docs and Insert
		for (int i = 0; i < elements; i++)
		{
			Docs d_object(object["response"]["docs"][i]["id"], object["response"]["docs"][i]["journal"], object["response"]["docs"][i]["eissn"],
				object["response"]["docs"][i]["publication_date"], object["response"]["docs"][i]["article_type"],
				GetAuthor(object,i), GetAbstract(object,i), object["response"]["docs"][i]["title_display"],
				object["response"]["docs"][i]["score"]);

			data.InsertDocs(d_object);
		}

		data.ShowTable();







		//std::cout << std::setw(4) << object << "\n\n";
		/*cout << object["response"]["numFound"] << endl;
		cout << object["response"]["docs"][0]["abstract"];*/







		

		//test
	/*	for (int i = 0; i < elements; i++)
		{
			cout << object.at("response").at("docs").at(i).at("id")<<endl;
		}*/

		/*auto author_elements = object["response"]["docs"][0]["author_display"].size();
		cout << author_elements << endl;*/
		//cout << object["response"]["docs"][0]["author_display"]<<endl;//print all 
		//cout << object.at("response").at("docs").at(0).at("author_display").at(0) << endl;
		
		
		
		

	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << '\n';
	}

	

	// fill a stream with JSON text
	
	//std::stringstream ss;
	//ss << text;

	//// parse and serialize JSON
	//json j_complete = json::parse(ss);
	//std::cout << std::setw(4) << j_complete << "\n\n";


	//// define parser callback
	//json::parser_callback_t cb = [](int depth, json::parse_event_t event, json& parsed)
	//{
	//	// skip object elements with key "Thumbnail"
	//	if (event == json::parse_event_t::key && parsed == json("Thumbnail"))
	//	{
	//		return false;
	//	}
	//	else
	//	{
	//		return true;
	//	}
	//};

	//// fill a stream with JSON text
	//ss.clear();
	//ss << text;

	//// parse (with callback) and serialize JSON
	//json j_filtered = json::parse(ss, cb);
	//std::cout << std::setw(4) << j_filtered << '\n';


















	//cout << "\nContent From http://www.york.ac.uk/teaching/cws/wws/webpage1.html " << endl;
	//try
	//{
	//    http::Request request{ "http://www.york.ac.uk/teaching/cws/wws/webpage1.html" };
	//    const auto response = request.send("GET");
	//    std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
	//}
	//catch (const std::exception& e)
	//{
	//    std::cerr << e.what() << '\n';
	//}


	//cout << "\nContent From http://tryphp.w3schools.com/demo/welcome_get.php?name=trieu&email=trieuphan " << endl;
	//try
	//{
	//    http::Request request{ "http://tryphp.w3schools.com/demo/welcome_get.php?name=trieu&email=trieuphan" };
	//    const auto response = request.send("GET");
	//    std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
	//}
	//catch (const std::exception& e)
	//{
	//    std::cerr << e.what() << '\n';
	//}

	//cout << "\nContent From http://tryphp.w3schools.com/demo/welcome_get.php?name=linhan&email=linhanphan " << endl;
	//try
	//{
	//    http::Request request{ "http://tryphp.w3schools.com/demo/welcome_get.php?name=linhan&email=linhanphan" };
	//    const auto response = request.send("GET");
	//    std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
	//}
	//catch (const std::exception& e)
	//{
	//    std::cerr << e.what() << '\n';
	//}
}

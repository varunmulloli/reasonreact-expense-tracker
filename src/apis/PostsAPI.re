let baseURL = "https://jsonplaceholder.typicode.com";

let fetchAllPosts = () => {
  APIHelper.makeRequest(baseURL ++ "/posts");
}
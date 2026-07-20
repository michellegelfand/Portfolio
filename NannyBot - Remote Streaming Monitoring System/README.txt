NannyBot is an independent project I spent about 2 months developing in my spare time.
I developed it to assist a PhD physics student at the Technion institute who was growing crystals in a lab as part of his study of superconductivity. He needed a "zoom style" programme that can run on the lab computer and record the crystals he is growing and video stream it to distant devices, so they can be monitored when he isn't physically in the lab. Similar to a "plant monitor", the programme was to start and stop recording at regular intervals (for example - record 10 seconds, then stop for 20 minutes. Repeat). The programme was to also display data scraped from the machines monitoring the crystals in the lab, info such as temperature, light angle etc. 

The programme contains a server side (to run in the lab) and a client side (to run at home). It utilizes Google Proto for efficiently transferring the data across the network. Later versions utilize json to save user settings such as theme colour (the client end has a user interface with menus... the user interface was made with qtgui). I used both signals and threads (multithreading) for efficient running of the programme. In one version I added a newsfeed that shows a random recent article title from online science magazines that can be clicked to open said article, just for fun to play with web scrapers).

The server is made to restart automatically in case of a crash. Upon startup a check is made whether this is a startup or a post-crash restart (if starting up, the user must enter info such as ip and recorder settings, if restarting - the startup menu is skipped and saved settings from the previous run are loaded).

I was yet to develop the component which couples the programme with the software used in the laboratory, when the PhD student changed the direction of his research due to new findings he uncovered. Nevertheless, this experience was a valuable challenge for me, as it was my first project in python, in which I am self taught. 


 


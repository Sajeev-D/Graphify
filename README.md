# Graphify

Graphify is a digital graphical calculator designed for basic analytical tasks. It can generate linear, quadratic, and cubic graphs. A distinctive feature of Graphify is its ability to calculate and display the points of intersection between any two graphs currently displayed on the screen. The screen can display up to four graphs simultaneously.

As for its input and output devices, users can select the type of function to graph and input the function’s coefficients using the keyboard. The keyboard uses a polling loop to get the PS2 data. Instructions for which keys to press on each screen are shown to aid in navigating Graphify. Each key press is accompanied by an audio playback, providing auditory feedback to confirm the input.

However, there are some functions which may not be obvious to the user, namely the add function, delete function, and finding intersection. Once on the graph screen:
1.	Adding a graph: Press the “A” key on the PS2 keyboard to add another plot of a graph.

2.	Deleting a graph: Select which graph to delete using the number row. A pink underline beneath the box corresponding to the colour of the graph will appear, confirming a selection. Then, press the “D” key to remove the graph.

3.	Finding intersections: Upon selecting 2 graphs using the steps described when deleting a graph, press the “I” key to display the intersection between the 2 selected graphs.

Additionally, the find intersection function is also accompanied by a distinct audio playback. This serves as a rewarding signal for the user’s achievement. The intersection points are sequentially displayed on the HEX display of the DE1soc board. The display switches every 1.5 seconds until the last intersection is displayed. The HEX display will only show intersection points that have values between 0 and 9 (inclusive) and truncate any decimals to an integer.




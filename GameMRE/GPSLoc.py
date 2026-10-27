from kivy.app import App
from kivy.uix.label import Label
from kivy.clock import Clock
from plyer import gps

class GPSLoc(App):
    def build(self):
        self.label = Label(text="Location")
        self.gps = gps
        self.gps.configure(on_location=self.on_location)
        self.gps.start()
        Clock.schedule_interval(self.get_location, 1)
        return self.label

    def get_location(self, *args):
        self.gps.get_location()

    def on_location(self, **kwargs):
        self.label.text = 'lat: {latitude}, lon: {longitude}'.format(**kwargs)

    def on_status(self, stype, status):
        self.label.text = 'GPS type={}\n{}'.format(stype, status)

    def on_stop(self):
        return super().on_stop()
    
class GpsTest(App):
    def build(self):
        self.label = Label(text="Waiting for GPS location...")
        self.start_gps()
        return self.label

    def start_gps(self):
        try:
            gps.configure(on_location=self.on_location, on_status=self.on_status)
            gps.start(minTime=1000, minDistance=0)
        except NotImplementedError:
            self.label.text = "GPS is not implemented on your platform"

    def on_location(self, **kwargs):
        self.label.text = f"Latitude: {kwargs['lat']}\nLongitude: {kwargs['lon']}"

    def on_status(self, stype, status):
        self.label.text = f"GPS status: {status}"

    def on_stop(self):
        gps.stop()
    
if __name__ == "__main__":
    # GPSLoc().run()
    GpsTest().run()
const express = require("express");
const router = express.Router();
const Doctor = require("../models/Doctor");
const authMiddleware = require("../middleware/authMiddleware");

router.get(
  "/",
  authMiddleware(["admin", "assistant", "patient"]),
  async (req, res) => {
    try {
      const doctors = await Doctor.find();
      res.json(doctors);
    } catch (err) {
      res.status(500).json({ message: err.message });
    }
  }
);

router.get("/schedule", authMiddleware(["doctor"]), async (req, res) => {
  try {
    const doctor = await Doctor.findOne({ userId: req.user.id });
    const appointments = await Appointment.find({ doctorId: doctor._id });
    res.json(appointments);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.get("/:id/availability", async (req, res) => {
  try {
    const doctor = await Doctor.findById(req.params.id);
    res.json(doctor.availability);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

module.exports = router;

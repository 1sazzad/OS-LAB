const express = require("express");
const router = express.Router();
const Appointment = require("../models/Appointment");
const authMiddleware = require("../middleware/authMiddleware");

router.get(
  "/",
  authMiddleware(["admin", "assistant", "patient", "doctor"]),
  async (req, res) => {
    try {
      let query = {};
      if (req.user.role === "patient") {
        const patient = await Patient.findOne({ userId: req.user.id });
        query.patientId = patient._id;
      } else if (req.user.role === "doctor") {
        const doctor = await Doctor.findOne({ userId: req.user.id });
        query.doctorId = doctor._id;
      }
      const appointments = await Appointment.find(query);
      res.json(appointments);
    } catch (err) {
      res.status(500).json({ message: err.message });
    }
  }
);

router.get("/pending", authMiddleware(["assistant"]), async (req, res) => {
  try {
    const appointments = await Appointment.find({ status: "pending" });
    res.json(appointments);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.post("/", authMiddleware(["patient"]), async (req, res) => {
  try {
    const appointment = new Appointment({
      ...req.body,
      patientId: req.user.id,
      createdBy: req.user.id,
    });
    await appointment.save();
    res.json(appointment);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.put("/:id", authMiddleware(["assistant"]), async (req, res) => {
  try {
    const appointment = await Appointment.findById(req.params.id);
    appointment.status = req.body.status;
    if (req.body.status === "confirmed") {
      appointment.confirmedBy = req.user.id;
    } else if (req.body.status === "canceled") {
      appointment.canceledBy = req.user.id;
    }
    await appointment.save();
    res.json(appointment);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

module.exports = router;
